# Computer Environment Setting

## Category

* [Windows](#windows)
* [Ubuntu](#ubuntu)
* [MacOS](#macos)
* Editor:
  * [Visual Studio Code](#visual-studio-code)

## Windows 10

For windows OS, we'll use "Windows Subsystem for Linux" to use unix-command terminal.

In addition, we'll use "VSCode" based on "Windows Subsystem for Linux" instead of Windows.

Therefore, you have to install "Ubuntu on windows", and complete [Ubuntu OS environment setting](#ubuntu).

### 1. Open "Developer mode"

Steps: 設定(Setting) -> 更新與安全性(Update & Security) -> 開發人員專用(For developers) -> Select "開發人員模式"(Developer mode)
![Set Developer mode](./img/computer/SetDeveloperMode.png)

### 2. Enable "Windows Subsystem for Linux"

Steps:
  1. 左下角搜尋並開啟"開啟或關閉 Windows 功能"(Search & open "Turn Windows features on or off")
  ![Search Windows Feature](./img/computer/SearchWindowsFeature.png)

  1. 勾選"Windows 子系統 Linux 版"(Select "Windows Subsystem for Linux")  
  ![Windows Subsystem for Linux](./img/computer/UbuntuOnWindowsSetting.png)

  1. Install Ubuntu in Microsoft Store.  
  ![MicrosoftStore Ubuntu](./img/computer/MicrosoftStoreUbuntu.png)

  1. Open cmd and execute following command  
      ```
      $ bash
      ```
      ![Cmd Bash](./img/computer/cmdBash.png)

  1. Follow the [Ubuntu OS environment setting](#ubuntu).

## Windows 11

For windows OS, we'll use "Windows Subsystem for Linux" to use unix-command terminal.

In addition, we'll use "VSCode" based on "Windows Subsystem for Linux" instead of Windows.

Therefore, you have to install "Ubuntu on windows", and complete [Ubuntu OS environment setting](#ubuntu).

### 1. Open "Developer mode"

Steps: 設定(Setting) -> 隱私與安全性(Privacy & Security) -> 開發人員模式(For developers) -> Select "開發人員模式"(Developer mode)
![Set Developer mode](./img/computer/SetDeveloperModeWin11.png)

### 2. Enable "Windows Subsystem for Linux"

Steps:
  1. 設定(Setting) -> 應用程式(Applications) -> 更多 Windows 功能  
  ![Windows Feature](./img/computer/Win11WindowsFeature.png)

  1. 勾選"Windows 子系統 Linux 版"(Select "Windows Subsystem for Linux")  
  ![Windows Subsystem for Linux](./img/computer/Win11UbuntuOnWindowsSetting.png)

  1. Install Ubuntu in Microsoft Store.  
  ![MicrosoftStore Ubuntu](./img/computer/Win11UbuntuDownload.png)


### 3. Follow the [Ubuntu OS environment setting](#ubuntu).

## Ubuntu

Execute the following command to install google test library:
```shell
$ sudo apt-get update
$ sudo apt-get install g++
$ sudo apt-get install make
$ sudo apt-get install libgtest-dev
$ sudo apt-get install cmake
$ cd /usr/src/gtest
$ sudo cmake CMakeLists.txt
$ sudo make
$ cd lib
$ sudo cp *.a /usr/lib
```

## MacOS

### Install C++

C++ is installed with xcode command line tool on Mac OS. 
```shell
$ xcode-select --install
```

### Install Googletest
1. Execute following command in terminal to install [Homebrew](https://brew.sh/index_zh-tw).
    ```shell
    $ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    ```

2. Download [google test source](https://github.com/google/googletest/archive/release-1.8.0.zip)

3. Install googletest:

    ```shell
    $ brew install cmake
    $ cd ~/Downloads/googletest-release-1.8.0/googletest
    $ mkdir build
    $ cd build
    $ cmake -Dgtest_build_samples=ON -Dgtest_build_tests=ON ~/Downloads/googletest-release-1.8.0/googletest
    $ make
    $ sudo mkdir -p /usr/local/gtest
    $ sudo cp ~/Downloads/googletest-release-1.8.0/googletest/build/libgtest.a /usr/local/gtest
    $ sudo cp -r ~/Downloads/googletest-release-1.8.0/googletest/include /usr/local/gtest
    $ sudo mkdir -p /usr/local/lib
    $ sudo ln -snf /usr/local/gtest/libgtest.a /usr/local/lib/libgtest.a
    $ sudo mkdir -p /usr/local/include
    $ sudo ln -snf /usr/local/gtest/include/gtest /usr/local/include/gtest
    ```

## Visual Studio Code

**[Download link](https://code.visualstudio.com/download)**

### Install packages

If your OS is not Windows, please ignore the first and the second steps.

1. Install VSCode for WSL:
https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-wsl

2. Open your `cmd`，execute the command below:
    ```bash
    cd posd2023f_{你的學號}_HW
    bash
    code .
    ```
    ![](https://i.imgur.com/0obo7Ob.png)

    This means VSCode is installing the neccessary packages

    ![](https://i.imgur.com/YUMa73H.png)

    This means your VSCode is running on WSL
    
    ![](https://i.imgur.com/M5JCcGx.png)
