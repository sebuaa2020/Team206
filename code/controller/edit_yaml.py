import sys

def edit():
    fileName = sys.argv[1]
    data = ""
    with open(fileName, "r") as file_obj:
        lines = file_obj.readlines()
        start = True
        for line in lines:
            if start:
                data += "image: map.pgm\n"
                start = False
            else:
                data += line
    with open(fileName, 'w') as file_obj2:
        file_obj2.write(data)

edit()