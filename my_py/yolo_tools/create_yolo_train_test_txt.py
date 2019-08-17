import os
import argparse

parser = argparse.ArgumentParser(description='where path')
parser.add_argument('--dir', default=".", type=str, help='dir_path')
parser.add_argument('--p', default=1, type=float, help='%% divide train and test')
#parser.add_argument('--sdir', default=".", type=str, help='dir_path')
args = parser.parse_args()

if __name__ == "__main__":
    if args.dir:
        dir_path = args.dir
    else:
        dir_path = '.'
    assert os.path.exists(dir_path),"dir path is not exist."
    if not dir_path.endswith('/'):
        dir_path = dir_path + '/'
    filelist = os.listdir(dir_path)

    pnglist = list(filter(lambda x: x.endswith('.png'),filelist))
    train_p = int(args.p * len(pnglist))
    with open(dir_path+"train.txt",mode="wt") as file:
        for filename in pnglist[:train_p]:
            file.write(dir_path+filename+'\n')
    with open(dir_path+"test.txt",mode="wt") as file:
        for filename in pnglist[train_p:]:
            file.write(dir_path+filename+'\n')
            
