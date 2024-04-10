use std::time::{SystemTime, UNIX_EPOCH};
use std::env;
use std::io::{Write};
use log::{error, debug};


const ARGS_ERROR: &str = "Usage: ./ft_otp [Option] [File]\n\
Try './ft_otp --help or -h' for more information.\n";

const HELP : &str = "Usage: ./ft_otp [Option] [File]\n\
Options:\n\
\t-g, --generate	Generate a new key and store it in \"ft_otp.key\" (encrypted).\n\
\t-k, --key	Generate a OTP using the key stored in \"ft_otp.key\".\n\
\t--help, -h	Display this help and exit.\n";

fn	arguments_check(args: &Vec<String>) {
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
		
		let mut hex_key = std::fs::read_to_string(args[2].clone()).expect("Unable to read file");
		hex_key = hex_key.trim().to_string();
		println!("Key: {}", hex_key);
		debug!("Hex key: {}", hex_key);
		if hex_key.len() != 64 || hex_key.chars().all(|c| c.is_ascii_hexdigit()) == false {
			error!("Expected 64 hexadecimal characters: {}", hex_key.len());
			std::process::exit(1);
		}
	}
	if args[1] == "-k" || args[1] == "--key" {
		let contents = std::fs::read_to_string("ft_otp.key").expect("Unable to read file");
		debug!("File content: {}", contents);
		let mut _hex_key = contents.trim().to_string();
	} 
}


fn main() {
	let args: Vec<String> = env::args().collect();
	env_logger::init();
	arguments_check(&args);

	let now = SystemTime::now();
	let since_the_epoch = now.duration_since(UNIX_EPOCH).expect("Time went backwards");
	println!("Since the epoch: {:?}", since_the_epoch);
	let timestamp = since_the_epoch.as_secs();
	println!("Timestamp: {}", timestamp);
}