import os
import argparse
from shutil import move
from tqdm import tqdm

parser = argparse.ArgumentParser(description='where path')
parser.add_argument('--dir', default=".", type=str, help='dir_path')
parser.add_argument('--b', default=50, type=int, help='batch size in a file')
parser.add_argument('--f',default='batch',type=str,help='batch file name')
parser.add_argument('--ext',default='png',type=str,help='file extension')
#parser.add_argument('--sdir', default=".", type=str, help='dir_path')
args = parser.parse_args()

if __name__ == "__main__":
    dest_dir = args.dir
    assert os.path.exists(dest_dir),"dir path is not exist."
    os.chdir(dest_dir)
    end_with = args.ext
    assert end_with in ['png','txt','jpg','.png','.txt','.jpg'],"extension {} is not supported".format(endwith)
    if not end_with.startswith('.'):
        end_with = '.' + end_with

    filelist = os.listdir(dest_dir)
    filterated_list = list(filter(lambda x: x.endswith(end_with),filelist))
    count = 0
    num = 1
    for filename in tqdm(filterated_list):
        batch_name = args.f + str(num)
        if not os.path.exists(batch_name):
            os.mkdir(batch_name)
        move(filename, batch_name)
        count += 1
        if count >= args.b:
            count = 0
            num += 1
