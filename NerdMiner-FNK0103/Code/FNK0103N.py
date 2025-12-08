import sys
import os
import subprocess
import platform

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))

FIRMWARE_DIR = os.path.abspath(os.path.join(SCRIPT_DIR, '..', 'Bin', 'FNK0103N'))

FIRMWARE_CONFIG = [
    {"file": "bootloader.bin", "offset": 0x1000},  # 4096
    {"file": "partitions.bin", "offset": 0x8000},  # 32768
    {"file": "boot_app0.bin",  "offset": 0xE000},  # 57344
    {"file": "firmware.bin",   "offset": 0x10000}  # 65536
]
VENV_DIR = os.path.join(SCRIPT_DIR, ".venv")
REQUIRED_PACKAGES = ["esptool", "pyserial"]
# ==============================================================

def is_running_in_venv():
    return sys.prefix != sys.base_prefix

def get_venv_python_path():
    if platform.system() == "Windows":
        return os.path.join(VENV_DIR, "Scripts", "python.exe")
    else:
        return os.path.join(VENV_DIR, "bin", "python")

def ensure_environment():
    try:
        import esptool
        import serial.tools.list_ports
        return
    except ImportError:
        if is_running_in_venv():
            print("[Init] Dependencies missing inside virtual environment. Attempting repair...")
            subprocess.check_call([sys.executable, "-m", "pip", "install"] + REQUIRED_PACKAGES)
            return

        venv_python = get_venv_python_path()

        if os.path.exists(venv_python):
            subprocess.call([venv_python, __file__] + sys.argv[1:])
            sys.exit(0)

        print("[Init] Creating virtual environment in 'Code' directory...")
        
        if not os.path.exists(VENV_DIR):
            import venv
            print(f"[Init] Creating directory: {VENV_DIR}")
            venv.create(VENV_DIR, with_pip=True)
        
        if not os.path.exists(venv_python):
            print(f"[Error] Python interpreter not found at: {venv_python}")
            sys.exit(1)

        print("[Init] Installing required libraries (esptool)...")
        try:
            subprocess.check_call([venv_python, "-m", "pip", "install"] + REQUIRED_PACKAGES)
        except subprocess.CalledProcessError:
            print("[Error] Failed to install dependencies. Please check your internet connection.")
            sys.exit(1)

        print("[Init] Environment ready. Restarting script...\n" + "="*50)
        subprocess.call([venv_python, __file__] + sys.argv[1:])
        sys.exit(0)

def find_serial_ports():
    import serial.tools.list_ports
    ports = list(serial.tools.list_ports.comports())
    return [p.device for p in ports]

def check_and_get_file_paths():
    valid_files = []
    missing_files = []

    if not os.path.exists(FIRMWARE_DIR):
        print(f"[Error] Directory not found: {FIRMWARE_DIR}")
        return None

    for item in FIRMWARE_CONFIG:
        full_path = os.path.join(FIRMWARE_DIR, item["file"])
        if os.path.exists(full_path):
            valid_files.append((full_path, str(item["offset"])))
        else:
            missing_files.append(item["file"])
    
    if missing_files:
        print(f"[Error] The following files are missing in {FIRMWARE_DIR}:")
        for f in missing_files:
            print(f"  - {f}")
        return None
        
    return valid_files

def main():
    ensure_environment()
    import esptool
    print("\n=== NerdMiner-FNK0103N(3.5'' ST7796 TN) ===")
    flash_list = check_and_get_file_paths()
    if not flash_list:
        input("File check failed. Press Enter to exit...")
        return
    ports = find_serial_ports()
    selected_port = ""
    
    if len(ports) == 1:
        selected_port = ports[0]
        print(f"[Port] Automatically selected port: {selected_port}")
    elif len(ports) > 1:
        print("Multiple ports detected:")
        for i, p in enumerate(ports):
            print(f" [{i}] {p}")
        try:
            idx_input = input("Please enter the index to select (default 0): ")
            idx = int(idx_input) if idx_input else 0
            selected_port = ports[idx]
        except:
            selected_port = ports[0]
            print(f"[Info] Invalid input, defaulting to: {selected_port}")
    else:
        print("[Port] No ports detected. Attempting to let esptool auto-detect.")
    cmd_args = [
        '--chip', 'esp32',
        '--baud', '921600',  
        '--before', 'default_reset',
        '--after', 'hard_reset',
        'write_flash',
        '-z',                
        '--flash_mode', 'dio',
        '--flash_freq', '40m',
        '--flash_size', 'detect'
    ]

    if selected_port:
        cmd_args = ['--port', selected_port] + cmd_args

    for full_path, offset in flash_list:
        cmd_args.append(offset)
        cmd_args.append(full_path)

    print("\n[Start] Flashing firmware to FNk0103...")
    print(f"Reference file path: {flash_list[0][0]}") 

    try:
        esptool.main(cmd_args)
        print("\n[Success] Firmware flashed successfully!")
    except Exception as e:
        print(f"\n[Fail] An error occurred: {e}")

if __name__ == '__main__':
    main()