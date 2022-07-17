# Better code to print possible words for the NYT Spelling Bee
import re, os, sys
from optparse import OptionParser

parser = OptionParser()
parser.add_option('--middle', '-m', action='store', dest='middle', 
                  help='[REQUIRED] The middle letter, please')
parser.add_option('--letters', '-l', action='store', dest='letters',
                  help='[REQUIRED] The other letters, please')
(ops, args) = parser.parse_args()

if ops.__dict__['middle'] is None:
    parser.error('Middle letter not given')
if ops.__dict__['letters'] is None:
    parser.error('Outside letters not given')
    
def pangram( letters, line):
    for single in letters:
        if not re.match(rf'^.*[{single}]+.*$', line):
            return False
    # At End
    return True

def main():
    # Transform args to lower
    middle = ops.middle.lower()
    letters = ops.letters.lower()

    # Simple Protections
    if len(middle) != 1:
        raise Exception('Error: please provide a single middle letter')
    elif len(letters) != 6:
        raise Exception('Error: please provide exactly six outside letters')
    elif not middle.isalpha() or not letters.isalpha():
        raise Exception('Error: only alphabet characters allowed')
    elif middle in letters:
        raise Exception('Error: middle letter should not also be in outside')

    # No duplicates
    dupcheck = set()
    for i in letters: dupcheck.add(i)
    if len(dupcheck) != 6:
        raise Exception('Error: no duplicate letters please')

    # Display Inputs
    print("You've inputted... ")
    print("    %s  "%(letters[0]))
    print("%s       %s"%(letters[5], letters[1]))
    print("    %s  "%(middle))
    print("%s       %s"%(letters[4], letters[2]))
    print("    %s  "%(letters[3]))

    # Get words
    myFile = open("words.txt")
    possibleWords = []
    pangrams = []
    for line in myFile:
        line = line.strip()
        if re.match(rf'^[{letters}{middle}]{{4,}}$', line):
            if re.match(rf'^.*{middle}.*$', line):
                possibleWords.append( line)
                if pangram( letters, line):
                    pangrams.append( line)

    # Print possible words
    print("There are %d possible words"%(len( possibleWords)))
    for i in possibleWords: print(i)

    # Print pangrams
    if len( pangrams) == 0:
        print("\nThere are no pangrams!")
    elif len( pangrams) == 1:
        print("\nThere are is only one possible pangram")
    else:
        print("\nThere are %d possible pangrams"%(len( pangrams)))
    for i in pangrams: print(i)
    
if __name__ == "__main__":
    try:
        main()
    except Exception as inst:
        print( inst.args[0])










