import os
import shutil

folds = ["times", "+", "-", "y"]

for i in folds:
    count = 0
    while count < 9000:
        for file in os.listdir(str(i)):
            shutil.copy(os.path.join(str(i), file), str(i)+"0\\"+str(count)+".jpg")
            print(str(i)+"\\"+str(count)+".jpg")
            count += 1
            if count == 9000:
                break