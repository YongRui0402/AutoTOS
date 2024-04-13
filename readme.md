# 專案介紹
本專案為C++開發的自動轉珠程式
* Demo: [Link](https://youtu.be/N7T8OkMcq6Y)
## 工具 Tools
* [轉珠模擬器](https://tower-of-saviors.github.io/website/canvas.html)
* [C/C++, mingw-builds-binaries](https://github.com/niXman/mingw-builds-binaries/releases)
* [Visual Studio Code](https://code.visualstudio.com/)
    * Code Runner
    * IntelliCode
    * C/C++ Extension Pack
## 注意事項
* VSC設定setting.json:  
    * C++解碼為Big5 
    * 設定鏈接器lgdi32 (Windows GDI)
    ```json=1
    {
        "cmake.configureOnOpen": true,
        // 讓 Code Runner 將 C++ 執行在終端機中
        "code-runner.runInTerminal": true,
        // 預設 C++ 程式碼的編碼方式為 Big5(繁體中文標準庫)
        "[cpp]":{
            "files.encoding": "Big5"
        },
        "code-runner.executorMap": {
            "c": "cd $dir && gcc $fileName -o $fileNameWithoutExt -lgdi32 && $dir$fileNameWithoutExt",
            "cpp": "cd $dir && g++ $fileName -o $fileNameWithoutExt -lgdi32 && $dir$fileNameWithoutExt",
        },
    }
    ```
## 目前程式問題與修改方向
* 20240413
    * 變數,參數,函數名稱不可讀
    * 程式架構混亂
    * 演算法尚可優化