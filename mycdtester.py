import subprocess
import difflib

testcases = open('testcases.txt', 'r')
testresults = open('testresults.txt', 'w')

input = []
output = []

for i in range(12):
    input.append(testcases.readline())
    output.append(testcases.readline())

for i in range(12):
    commandoutput = subprocess.check_output([input[i]], shell=True, text=True)
    status = (commandoutput == output[i])

    testresults.write("Test %s expected output: %s"%(i, status)) 
    if(not status):
        testresults.write("Expected output: %s  " % output[i])
        testresults.write("Recieved output: %s" % commandoutput)
        testresults.write([li for li in difflib.ndiff(output[i], commandoutput) if li[0]!=" "])
    testresults.write("\n")

testresults.close()
testcases.close()
