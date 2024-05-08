要在Visual Basic（例如在VB.NET中）將字串中的逗號 `,` 替換成分號 `；`，您可以使用 `Replace` 方法。以下是逐步說明：

1. 定義一個包含逗號的字串。
2. 使用 `Replace` 方法將逗號替換為分號。
3. 打印或以其他方式使用替換後的字串。

這裡有個範例代碼：

```vb
Dim originalString As String = "1111,2222,3333"
Dim modifiedString As String

' 使用Replace方法將逗號替換為分號
modifiedString = originalString.Replace(",", "；")

' 打印修改後的字串
Console.WriteLine(modifiedString)
```

這段代碼將輸出：

```
1111；2222；3333
```

只需將這些步驟應用於您的程式中即可實現替換功能。