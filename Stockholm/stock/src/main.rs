use std::env;
use std::path::Path;
use std::fs::File;
use std::io::Write;
use rand::{rngs::OsRng, RngCore};

fn options_parser(args: Vec<String>, _options: &mut String) {
	for s in args {
		println!("parser: {s}");
	}
	return ();
}

fn main() -> std::io::Result<()> {
    let args: Vec<String> = env::args().collect();

	let mut _options: String = String::from("h");

	match args.len() {
		2 | 3 | 4 | 5 => options_parser(args, &mut _options),
		1 | _ => println!("Nothing found..."),
	}

	let mut key = [0u8; 32];
	let mut nonce = [0u8; 24];
	
	OsRng.fill_bytes(&mut key);
	OsRng.fill_bytes(&mut nonce);
	
	let folder_key_path = "~/42-Cybersecurity/Stockholm/stock/key";
	let path = Path::new(folder_key_path);

	if path.is_dir() {
		
		let mut file = File::create("key.cript")?;
		file.write_all(&key)?;
		
		file = File::create("nonce.cript")?;
		file.write_all(&nonce)?;
	}

	Ok(())
}
