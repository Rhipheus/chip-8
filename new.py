myfile = "test/slipperyslope.ch8"

with open(myfile, "rb") as f:
    data=f.read()
    print(data.hex())