import os

# ./simulation -ma 1900000000 -ra 3:1 -mb 1900000000 -rb 1:1 >> out

command = "./simulation -ma 1900000000 -ra 3:1 -mb 1900000000 -rb 1:1"


retValue = os.system(command)
print(retValue)

