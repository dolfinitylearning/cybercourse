#-------------------------------------------------------------------------------
# Name:        module2
# Purpose:
#
# Author:      mathieso
#
# Created:     12/11/2013
# Copyright:   (c) mathieso 2013
# Licence:     <your licence>
#-------------------------------------------------------------------------------
import sys
def main():
    data_in = ''
    for line in sys.stdin:
        data_in += line
    print('You said:')
    print (data_in)

if __name__ == '__main__':
    main()
