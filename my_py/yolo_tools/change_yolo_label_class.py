import os
import argparse
from tqdm import tqdm

parser = argparse.ArgumentParser(description='where path')
parser.add_argument('--dir', default=".", type=str, help='dir_path')
parser.add_argument('--fr', default=0, type=str, help='replace what')
parser.add_argument('--to', default=0, type=str, help='to what')
args = parser.parse_args()

if __name__ == "__main__":
    if args.dir:
        dir_path = args.dir
    else:
        dir_path = '.'
    replace_from = args.fr if args.fr else '0'
    replace_to = args.to if args.to else '0'

    assert os.path.exists(dir_path),"dir path is not exist."
    if not dir_path.endswith('/'):
        dir_path = dir_path + '/'
    filelist = os.listdir(dir_path)

    confirm = input("Are you sure you want change the class contents of yolo class .txt files from \'{0}\' to \'{1}\' \
in the path of \'{2}\'? (Y/N)\n".format(replace_from,replace_to,dir_path))
    confirm = confirm.upper()
    if not confirm.startswith('Y'):
        exit("shut down!")
    else:
        print("start processing...")
    for filename in tqdm(filelist):
        de_path = os.path.join(dir_path, filename)
        if os.path.isfile(de_path):
            if de_path.endswith(".txt"):
                with open(de_path,mode='r', encoding='utf-8') as txtfile:
                    lines = txtfile.readlines()
                    #print(lines)
                with open(de_path,mode='wt',encoding='utf-8') as txtfile:
                    for line in lines:
                        if line.startswith(replace_from):
                            line = replace_to + line[len(replace_from):]
                        txtfile.write(line)