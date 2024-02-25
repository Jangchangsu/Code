from optparse import OptionParser
"""
parser = OptionParser(usage='usage: Calc.py -n <tgtNum> -o <operation>')
parser.add_option('-n', dest='tgtNum', type='string', help='write numbers with comma')
parser.add_option('-o', dest='operation', type='string', help='specify operation +-*/%')

(options, args) = parser.parse_args()

# Check if the required options are provided
if not (options.tgtNum and options.operation):
    parser.error('Please provide both -n and -o options.')

tgtNum = options.tgtNum.split(',')
oper = options.operation
operStr = ""

for num in tgtNum:
    operStr += num + oper

print(operStr)
print (type(operStr))
operStr = operStr[:-1]
print(operStr)
print (type(operStr))

print('result is', eval(operStr))
print (type(eval(operStr)))
"""
"""
parser = OptionParser()
parser.add_option('-f', '--input_file', default='/no/such/file', help='command file',
                  action='store', type='string', dest='input_file')

(options, args) = parser.parse_args()

path = options.input_file
print(path)

try:
    with open(path, 'r') as file:
        contents = file.read()
        print(contents)
except FileNotFoundError:
    print("File not found:", path)
except IOError as e:
    print("Error reading file:", e)
"""


class MyClass:
    def vprint(self, msg):
        print(msg, end='')

instance = MyClass()
path = '/a'
instance.vprint('op mkdir %s ->' % path)

