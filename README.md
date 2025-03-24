# Unreal Advanced Physics Project

## Prerequisites

Before building the project, ensure the following are installed:

1. **Unreal Engine 5.5**  
   Make sure Unreal Engine 5.5 is installed on your system. If it's not, you can download it via the Epic Games Launcher.

2. **Windows 10/11**  
   The instructions below are for Windows-based systems.

## Clone the Repository

To get started, first, clone the project repository:

```bash
git clone https://github.com/Attrixx/HungryBirds.git
```

Navigate to the project directory:

```bash
cd HungryBirds
```

## Build the Project

To build the project, follow these steps:

1. **Ensure Unreal Engine 5.4 is Installed**  
   The build script assumes Unreal Engine 5.4 is installed at the default location:
   `C:\Program Files\Epic Games\UE_5.4\`

   If you have Unreal Engine installed elsewhere, you may need to adjust the paths in the `build.bat` file.

2. **Run the Build Script**  
   Execute the `build.bat` file located in the root directory of the project. This script will automatically compile and build the project using Unreal Engine.

   To do this, double-click on the `build.bat` file or run the following command in Command Prompt:

   ```bash
   build.bat
   ```

   The build process will begin, and it may take some time depending on your system.

---

## Running the Project

After the build process is complete, the executable will be located in a generated directory under the `Binaries/` folder. Simply navigate to the `Binaries/` directory, and you will find the executable (e.g., `HungryBirds.exe`) inside the appropriate subfolder.

---

### Troubleshooting

- **Unreal Engine Not Found**  
   If you encounter issues with Unreal Engine not being found during the build, ensure Unreal Engine 5.5 is installed at the default location or update the `build.bat` file with the correct path to your Unreal Engine installation.

- **Missing Dependencies**  
   If there are any missing dependencies, the build process will notify you. Make sure your development environment is set up correctly, including the necessary C++ tools.
