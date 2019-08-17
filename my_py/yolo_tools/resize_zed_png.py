import os
from PIL import Image
from tqdm import tqdm

#TUDO add jindutiao
if __name__ == '__main__':
    print("Starting crop...")
    count = -1
    dir_path = "/home/xue/Documents/ZED/"
    save_path = dir_path+"processed_img/"
    if  not os.path.exists(save_path): #如果路径不存在
        os.makedirs(save_path)

    for pic in tqdm(os.listdir(dir_path)):
        if not pic.endswith('.png'):
            continue
        count += 2
        im = Image.open(dir_path+pic)

        out1 = im.crop((0,0,im.width//2,im.height))
        out2 = im.crop((im.width//2,0,im.width,im.height))
        out1.save(save_path+"{:0>4d}".format(count)+".png")
        out2.save(save_path+"{:0>4d}".format(count+1)+".png")
    print("Finished!")
    print("Processed image saved in ",save_path)