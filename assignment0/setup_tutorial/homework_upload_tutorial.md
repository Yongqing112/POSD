# Homework Upload Tutorial

## 在本地端上初次下載遠端資料夾

1. 在想要放置專案資料夾的地方開啟終端機(ex. 我想要將資料夾放置於桌面，則將終端機路徑調整為桌面)

1. 前往Gitlab (http://140.124.181.100) 並找到自己的專案 並複製其路徑(建議用HTTP)

1. 將專案Clone下來。
輸入指令: git clone ${{URL}}

## 將本地端檔案同步至遠端資料夾

1. 確認專案當前狀態。
輸入指令: git status

1. 將新增/變更的檔案加入欲同步檔案之佇列
輸入指令: git add ${{檔案名稱}}
備註: 欲一次加入全部檔案則 **git add .** 點不是打錯，就是點。

1. 再次確認專案狀態。
輸入指令: git status

1. 確認無誤後，將此次變更commit至本地端版控
輸入指令: git commit -m ${{自訂變更訊息}}
備註: 如果你是第一次 commit ， 會需要輸入你的身分(email & name)
輸入指令範例: git config --global user.email "t111598015@ntut.org.tw"
             git config --global user.name "Richard"

1. 將本地端紀錄同步至 Gitlab。
輸入指令: git push -u origin master
輸入你的 Gitlab Username 及 Password
備註: Password在輸入時不會出現任何字

1. 回到 Gitlab 確認作業上傳狀態
