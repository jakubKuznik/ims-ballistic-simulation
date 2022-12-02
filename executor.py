import os

# ./simulation -ma 1900000000 -ra 3:1 -mb 1900000000 -rb 1:1 >> out
curDir = os.path.abspath(".")

# 3:1 === 75% offensive 25% deffensive 
command = "./simulation -ma 1900000000 -ra 3:1 -mb 1900000000 -rb 1:1"

retValue = os.system(command)


# 1:2
# 1:3
# 1:4
# 1:5
# 2:1
# 3:1
# 4:1
# 5:1

# todo vyrobit 1:1 referencni  

# 1700000000
# 1800000000
# 1900000000
# 2000000000

## SAME MONEY 
##cmd = ""
##for i in range(2,6):
  ##for k in range(2,6):
    ##for x in range(2,6):
      ##for y in range(2,6):
        ##for i in range(10):
          ##cmd = "./simulation -ma 1900000000"
          ##cmd += " -ra " + str(i) + ":" + str(k) + " -mb 1900000000" + " -rb " + str(x) + ":" + str(y) + " >> output" + str(j)
          ##os.system(cmd)
          ##print(cmd)

cmd = ""
for j in range(1950000000,2000000001,10000000):
  for i in range(2,6):
    for k in range(2,6):
      for x in range(2,6):
        for y in range(2,6):
          cmd = "./simulation -ma 1900000000"
          cmd += " -ra " + str(i) + ":" + str(k) + " -mb " + str(j) + " -rb " + str(x) + ":" + str(y) + " >> output_smaller" + str(j)
          os.system(cmd)
          print(cmd)