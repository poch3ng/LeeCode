如果你有一個函式，需要在非同步（`Async`）和同步的環境中都能被使用，你可以考慮以下幾種方法來設計你的代碼：

### 1. 抽象共用邏輯

將可重用的邏輯抽取到一個單獨的方法中，然後在非同步和同步方法中調用它。這可以減少代碼重複，並保持業務邏輯的一致性。

#### 示例：

```vb
' 基礎邏輯函式
Private Function BasicOperation(input As String) As String
    ' 基礎處理邏輯
    Return "Processed " & input
End Function

' 非同步函式
Public Async Function ProcessDataAsync(input As String) As Task(Of String)
    Await Task.Delay(1000)  ' 模擬非同步等待
    Return BasicOperation(input)
End Function

' 同步函式
Public Function ProcessData(input As String) As String
    Return BasicOperation(input)
End Function
```

### 2. 使用 `Task.Run` 在同步方法中調用非同步代碼

如果你的非同步函式主要用於長時間運行的背景任務，你可以在需要同步調用的地方使用 `Task.Run` 來包裝這些函式。這可以避免 UI 凍結，但仍然保持代碼的非同步性質。

#### 示例：

```vb
' 同步調用非同步函式
Public Function GetDataSynchronously(input As String) As String
    ' 使用 Task.Run 來在後台線程執行非同步方法
    Dim result As String = Task.Run(Function() ProcessDataAsync(input)).Result
    Return result
End Function
```

### 3. 避免使用 `.Result` 或 `.Wait()`

在 UI 應用程序中直接使用 `.Result` 或 `.Wait()` 可能會導致死鎖。如果需要從同步代碼中調用非同步方法，更好的選擇是使用 `Task.Run` 來管理這些調用。

### 4. 為非同步環境設計接口

如果可能的話，設計你的應用程序接口以支持非同步。這通常意味著，所有可能需要等待的操作（如 IO 操作或網絡請求）都應該是非同步的。

### 結論

設計可以在非同步和同步環境中使用的函式時，你應該確保將邏輯分離，使得非同步處理的部分保持靈活和可重用。如果你的應用場景允許，儘量推廣使用非同步方法，這樣可以獲得更好的性能和更高的響應性。