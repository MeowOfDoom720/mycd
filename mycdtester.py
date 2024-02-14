import subprocess
import difflib

testcases = open('testcases.txt', 'r')
testresults = open('testresults.txt', 'w')
testcount = 12

input = []
output = []

for i in range(testcount):
    testcases.readline()
    inline = testcases.readline()
    outline = testcases.readline()
    input.append(inline[inline.find('=')+1:])
    output.append(outline[outline.find('=')+1:])
    testcases.readline()

for i in range(testcount):
    commandoutput = subprocess.check_output([input[i]], shell=True, text=True)
    status = (commandoutput == output[i])

    testresults.write("Test %s: %s"%(i+1, "PASS" if status else "FAIL"))
    testresults.write("\nArgs: %s" % (input[i][6:]))
    testresults.write("Program Output: %s"%commandoutput)

    if(not status):
        testresults.write("\nExpected output: %s  " % output[i])
        testresults.write([li for li in difflib.ndiff(output[i], commandoutput) if li[0]!=" "])
    testresults.write("\n")

testresults.close()
testcases.close()
