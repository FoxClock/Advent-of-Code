import datetime
import os
import sys
import requests
import argparse
from bs4 import BeautifulSoup

# ====================================
# == Constants =======================
CURRENT_DATE=datetime.date.today()
CURRENT_DIR=os.getcwd()

# The month AOC is held in
DECEMBER= 12

FILES = {
        'Puzzle_input': 'input.txt',
        'Sample_input': 'sample_input.txt',
        }

MAKEFILE = '''
CC=cc
Day={}
challenge1=Day$(Day)
challenge2=Day$(Day)-2
commonPath=../Common
common=common
flags=-Wextra

all: AOC-challenge1
    $(CC) -o AOC$(Day) *.o
    chmod +x AOC$(Day)

AOC-challenge1: $(challenge1).c common
    $(CC) -c $(challenge1).c $(flags)

AOC-challenge2: $(challenge2).c common
    $(CC) -c $(challenge2).c $(flags)

common: $(commonPath)/$(common).c $(commonPath)/$(common).h
    $(CC) -c $(commonPath)/$(common).c

clean:
    rm *.o
    rm AOC$(Day)

run:
    ./AOC$(Day)
'''

# =====================================
# == Request data =====================
HEADERS = {
    'cookie': 'session=53616c7465645f5fb1118dfc769f02a022f56fc03e600a9ca46b508d80ae5e980e944b171aa9ed858e41b41c7275e53ae402b67ee396289fd6ddcef8033067d6',
    'user-agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.0.0 Safari/537.36',
}


# =====================================
# == Calculate date ===================

def AOC_date(date: datetime.date) -> int:
    ''' determine the AOC challenge date '''
    # Get the current day of the month
    if date.month == DECEMBER:
        day: int = date.day
    else:
        raise ValueError("invalid date")

    return day

# =====================================
# == get web contents =================
def get_sample(year: int, day: int) -> str:
    ''' Get AOC html '''

    ## Variables
    url: str = f'https://adventofcode.com/{year}/day/{day}'
    print(f'Retrieving from: {url}')
    response = requests.get(headers=HEADERS, url=url)

    # TODO: actually retrieve sample
    return ''

# =====================================
# == get test input ===================
def get_input(year: int, day: int) -> str:
    '''Get the puzzle input for a day in a year'''
    url = f'https://adventofcode.com/{year}/day/{day}/input'
    print(f'Retrieving from: {url}')
    response = requests.get(headers=HEADERS, url=url, timeout=5)

    return response.text

# ====================================
# == write files =====================

def write_input(file_name: str, input_text: str):
    '''Write out input file'''
    if not input_text:
        print('No input, writing empty file.')
        input = ''

    with open(file_name, 'w', encoding='utf-8') as file:
            file.write(input_text)

def write_makefile(day: int):
    ''' Write the make file for the c code'''
    # Open the file
    with open('Makefile', "w", encoding='utf-8') as file:
        file.write(MAKEFILE.format(day))


# =====================================
# == setup a day ======================
def setup_day(day: int):
    ''' Sets up a day from the AOC'''
    ## Variables
    # Get the current year
    current_year: int = CURRENT_DATE.year
    input_text: str
    directory_name = f'./day{day}'

    # Retrieve challenge sample
    # TODO: implement challenge sample retrieval

    # Retrieve challenge input
    challenge_input: list[str] = []
    try:
        # Get the day's input
        # Placed in reverse order, as they are popped off the
        # list.
        challenge_input.append(get_sample(current_year, day))
        challenge_input.append(get_input(current_year, day))

    except requests.exceptions.RequestException as e:
        print(f'An error ocurred: {e}')

    # Check for directory
    if not os.path.exists(directory_name):
        # Make directory
        os.mkdir(directory_name)

        # cd into directory
        os.chdir(directory_name)

        for file in FILES.keys():
            write_input(file, challenge_input.pop())

       # Write the make file to the directory 
        write_makefile(day)

# ======================================
# == Main function =====================
def main(*args):

    # allow user to pass a particular day to get input for
    parse = argparse.ArgumentParser(
        description='Get AOC input and test input for a given day. If no arguments passed, defaults to current day',
    )
    parse.add_argument('--day', help='Day to get puzzle input for.')

    args = parse.parse_args()
    if args.day:
        print(f'Retrieving day: {args.day}...')
        setup_day(args.day)
    else:
        print(f'Using default: Current day challenge...')
        # Retrieve current AOC day
        day = AOC_date(CURRENT_DATE)
        setup_day(day)


if __name__ == '__main__':
    main()
