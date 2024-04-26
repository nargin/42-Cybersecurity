use std::time::{SystemTime, UNIX_EPOCH};
use std::env;
use std::io::{Write, Read};
use log::{error, debug};
use std::fs::File;
use ring::hmac;

extern crate base32;

use base32::{Alphabet, encode, decode};

const ARGS_ERROR: &str = "Usage: ./ft_otp [Option] [File]\n\
Try './ft_otp --help or -h' for more information.\n";

const HELP : &str = "Usage: ./ft_otp [Option] [File]\n\
Options:\n\
\t-g, --generate	Generate a new key and store it in \"ft_otp.key\" (encrypted base32).\n\
\t-k, --key	Generate a OTP using the key stored in \"ft_otp.key\".\n\
\t--help, -h	Display this help and exit.\n";

#[derive(PartialEq)]
enum Option {
	Generate,
	Key,
	Error,
}

fn generate_encoded_key(input: &str) {
	let input_string = match File::open(input) {
		Ok(_) => {
			let contents = std::fs::read_to_string(input).expect("Unable to read file");
			contents
		},
		Err(_) => {
			input.to_string()
		},
	};
	println!("Hex secret: {}", input_string);
	let secret_key = input_string.as_bytes();
	println!("Length: {}", secret_key.len());
	let encoded_key = encode(Alphabet::RFC4648 { padding: true }, secret_key);
	println!("Key (base32): {}", encoded_key);
	// let res = generate_hotp(b"FVNEOSGW3MDAJHOEFJCH4BJGSQ77QYYDVXVD53F2DVKSYMQWTOWA====", 0);
	// println!("OTP: {}", res);
	// let mut file = std::fs::File::create("ft_otp.key").expect("Unable to create file");
	// file.write_all(encoded_key.as_bytes()).expect("Unable to write data");
	// debug!("Key (base32): {}", encoded_key);
	// debug!("Key stored in \"ft_otp.key\"");

}

HE3TQRSGIQ4UKMZQIJDDSRKGIYYUKRCBGYYTSQJXGFBUIRKFIY3TKNZWGQ2EMMRXIZCDMOCDGU3UIMZVG44TMMBUIUZDAQRQIVATONA=

fn generate_hotp(secret_key: &[u8], counter: u64) -> String {
	let counter_bytes = counter.to_be_bytes();
	let key = hmac::Key::new(hmac::HMAC_SHA1_FOR_LEGACY_USE_ONLY, secret_key);
	let tag = hmac::sign(&key, &counter_bytes);

	let tag_bytes = tag.as_ref();
	let offset = (tag_bytes[tag_bytes.len() - 1] & 0x0f) as usize;
	let binary = ((tag_bytes[offset] as u32 & 0x7f) << 24) |
		((tag_bytes[offset + 1] as u32) << 16) |
		((tag_bytes[offset + 2] as u32) << 8) |
		(tag_bytes[offset + 3] as u32);

	let otp = binary % 10u32.pow(6 as u32);
	format!("{:01$}", otp, 6)
}

fn generate_totp(input: &str) {
	let content = std::fs::read_to_string(input).expect("Unable to read file");
	let secret_key = base32::decode(Alphabet::RFC4648 { padding: false }, content.as_str()).expect("Unable to decode key");
	let time = SystemTime::now().duration_since(UNIX_EPOCH).expect("Unable to get time").as_secs();
	let counter = time / 30;
	let otp = generate_hotp(&secret_key, counter);
	println!("Time based OTP: {}", otp);
}


fn test_permissions() {
	let tested_string = String::from("Ohaio mina-san!~~");
	let mut file = std::fs::File::create("test.tmp").expect("Unable to create file");
	debug!("Test file created at {}", std::fs::canonicalize("test.tmp").expect("Unable to get file path").display());
	file.write_all(tested_string.as_bytes()).expect("Unable to write data");
	let contents = std::fs::read_to_string("test.tmp").expect("Unable to read file");
	if contents != tested_string {
		debug!("Contents: \"{}\" but expected \"{}\"", contents, tested_string);
		std::fs::remove_file("test.tmp").expect("Unable to remove file");
		std::process::exit(1);
	}
	debug!("File content: {}", contents);
	std::fs::remove_file("test.tmp").expect("Unable to remove file");
}

fn	arguments_check(args: &Vec<String>) -> Option {
	if args.len() > 1 && (args[1] == "--help" || args[1] == "-h") {
		println!("{}", HELP);
		std::process::exit(0);
	}
	if args.len() != 3 {
		error!("Arguments error: {:?}", args);
		error!("Number of arguments: {}", args.len());
		println!("{}", ARGS_ERROR);
		std::process::exit(1);
	}
	if args[1] != "-g" && args[1] != "--generate" && args[1] != "-k" && args[1] != "--key" {
		error!("Invalid option: {}", args[1]);
		println!("{}", ARGS_ERROR);
		std::process::exit(1);
	}
	if args[1] == "-g" || args[1] == "--generate" {
		test_permissions();
		match File::open(args[2].clone()) {
			Ok(_) => {
				let contents = std::fs::read_to_string(args[2].clone()).expect("Unable to read file");
				if contents.len() < 64 && contents.chars().all(|c| c.is_ascii_hexdigit()) { 
					error!("Invalid key: {}", contents);
					std::process::exit(1);
				}
				debug!("File content: {}", contents);
				return Option::Generate;
			},
			Err(_) => {
				if args[2].len() < 64 && args[2].chars().all(|c| c.is_ascii_hexdigit()) { 
					error!("Invalid key: {}", args[2]);
					std::process::exit(1);
				}
				debug!("Key: {}", args[2]);
				return Option::Generate;
			},
		}
	}
	if args[1] == "-k" || args[1] == "--key" {
		test_permissions();
		match File::open(args[2].clone()) {
			Ok(_) => {
				if args[2] != "ft_otp.key" {
					error!("Invalid file: {}", args[2]);
					std::process::exit(1);
				}
				return Option::Key;
			},
			Err(_) => {
				return Option::Error;
			},
		}
	}
	return Option::Error;
}


fn main() {
	let args: Vec<String> = env::args().collect();
	env_logger::init();
	// let _option = arguments_check(&args);

	generate_encoded_key("hex.key");

	// match option {
	// 	Option::Generate => {
	// 		generate_encoded_key(&args[2]);
	// 	},
	// 	Option::Key => {
	// 		generate_totp(&args[2]);
	// 	},
	// 	Option::Error => {
	// 		println!("{}", ARGS_ERROR);
	// 		std::process::exit(1);
	// 	},
	// }
}