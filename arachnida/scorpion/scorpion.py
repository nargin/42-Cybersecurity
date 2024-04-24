import argparse
import exiftool
import os
import json

Extension = ["png", "jpg", "jpeg", "gif", "bmp"]

def	isFileValid(file):
	ext = file.split(".")[-1]
	if not os.path.exists(file):
		raise FileNotFoundError(f"File {file} not found")
	if not os.path.isfile(file):
		raise ValueError(f"{file} is not a file")
	if not os.access(file, os.R_OK):
		raise PermissionError(f"Permission denied to read {file}")
	if ext not in Extension:
		raise ValueError(f"File {file} is not an image file")
	

def main():
	parser = argparse.ArgumentParser(description='Metadata of a file', prog='Scorpion')
	parser.add_argument("file", help="File to extract metadata from", type=str, nargs="+")
	args = parser.parse_args()

	for file in args.file:
		isFileValid(file)

	for file in args.file:
		with exiftool.ExifToolHelper() as et:
			metadata = et.get_metadata(file)
			metadata = json.dumps(metadata, indent=4)
			print(metadata)

if __name__ == "__main__":
	main()