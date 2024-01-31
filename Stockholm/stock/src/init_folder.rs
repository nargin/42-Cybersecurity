use std::path::Path;
use std::env;
use std::fs;
use std::fs::File;
use std::io::Write;

pub fn init_folder_and_key_files(key: [u8; 32], nonce: [u8; 24]) -> Result<&'static str, &'static str> {

	let exe_path = env::current_exe().unwrap();
	
	let mut key_folder_path = String::from(exe_path.to_string_lossy());
	
	while key_folder_path.chars().last() != Some('/') {
		key_folder_path.pop();
	}

	key_folder_path += "key"; // $HOME/$USER/$REPO/Stockholm/stock/target/debug/ + key
	println!("exe Path: {}", key_folder_path);

	if fs::metadata(&key_folder_path).is_err() {
		if let Err(_) = fs::create_dir(key_folder_path.clone()) {
			return Err("Can't create key folder");
		}
	}
	let key_folder = Path::new(key_folder_path.as_str());

	if key_folder.is_dir() {
		
		let result = File::create(key_folder_path.clone() + "/key.cript");

		let mut file = match result {
			Ok(file) => file,
			Err(_) => return Err("Can't create key.cript file"),
		};
		let _ = file.write_all(&key);
		
		let result = File::create(key_folder_path + "/nonce.cript");

		let mut file = match result {
			Ok(file) => file,
			Err(_) => return Err("Can't create nonce.cript file"),
		};
		let _ = file.write_all(&nonce);
	}

	return Ok("Folder and files created succesfully");
}