from bs4 import BeautifulSoup
import requests
import argparse
import os
from enum import Enum

class Extension(Enum):
	PNG = ".png"
	JPG = ".jpg"
	JPEG = ".jpeg"
	GIF = ".gif"
	BMP = ".bmp"

class Arachnida:
	def __init__(self, url, path="./data/", level=5):
		self.url = url
		self.path = path
		self.level = level
		depth_url_level_valider(url, level)

	def depth_url_level_valider(self, url, level):
		if level < 0:
			raise ValueError("Depth level cannot be negative")
		if level == 0:
			return
		page = requests.get(url)
		soup = BeautifulSoup(page.content, 'html.parser')
		links = soup.find_all("a", href=True)
		for link in links:
			if level == 0:
				break
			depth_url_level_valider(link["href"], level-1)
		

	def extract_data(self, path, url):
		page = requests.get(url)
		soup = BeautifulSoup(page.content, 'html.parser')
		
		img_tags = soup.find_all("img")

		os.makedirs(path, exist_ok=True)
		# link = soup.find_all("link", href=True)

		img_count = 1

		for img in img_tags:
			img_url = img["src"]
			if not img_url.startswith("https://") and not img_url.startswith("http://"):
				img_url = url + img_url
			img_data = requests.get(img_url).content

			with open(f"{path}/image{img_count}.jpg", "wb") as handler:
				handler.write(img_data)
				img_count += 1
	


def main():
	parser = argparse.ArgumentParser(description='Extract data from a web page', prog='Arachnida')
	parser.add_argument("-r", "--recursively", help="Recursively extract data from all links", action="store_true")
	parser.add_argument("-l", "--level", help="Depth level limit for recursive extraction", type=int, default=5)
	parser.add_argument("-p", "--path", help="Path to save the data extracted (default: ./data/)", default="./data/")
	parser.add_argument("url", help="URL to extract data from")
	args = parser.parse_args()
	
	arachnida = Arachnida(args.url, args.path, args.level)

if __name__ == "__main__":
	main()