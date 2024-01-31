use std::env;
use rand::{rngs::OsRng, RngCore};

mod init_folder;
use init_folder::init_folder_and_key_files;

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

	match init_folder_and_key_files(key, nonce) {
		Ok(g) => println!("Init: {}", g),
		Err(e) => {
			eprintln!("Error occured: {}", e);
			std::process::exit(127);
		},
	};

	Ok(())
}
