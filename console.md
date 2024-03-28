在Visual Basic中將多個變量的值輸出到控制台（Console），有幾種不同的方法。以下介紹幾種常見的方式，這些方法可以根據您的具體需要進行選擇和使用：

### 方法1：使用`Console.WriteLine()`
您可以使用`+`或`&`來連接字符串和變量，然後使用`Console.WriteLine()`方法來輸出。

```vb
Dim name As String = "David"
Dim age As Integer = 30
Dim location As String = "Taiwan"

Console.WriteLine("Name: " & name & ", Age: " & age.ToString() & ", Location: " & location)
```

### 方法2：使用字符串插值（僅限VB 14及以上版本）
如果您使用的是VB 14或更高版本，可以使用字符串插值的方式，這樣代碼會更加簡潔易讀。

```vb
Dim name As String = "David"
Dim age As Integer = 30
Dim location As String = "Taiwan"

Console.WriteLine($"Name: {name}, Age: {age}, Location: {location}")
```

### 方法3：使用`String.Format()`
`String.Format()`方法允許您創建一個格式化的字符串，然後將其輸出到控制台。

```vb
Dim name As String = "David"
Dim age As Integer = 30
Dim location As String = "Taiwan"

Console.WriteLine(String.Format("Name: {0}, Age: {1}, Location: {2}", name, age, location))
```

### 方法4：逐個輸出
如果不需要在一行中輸出所有變量，您可以選擇逐個輸出它們。

```vb
Dim name As String = "David"
Dim age As Integer = 30
Dim location As String = "Taiwan"

Console.WriteLine("Name: " & name)
Console.WriteLine("Age: " & age.ToString())
Console.WriteLine("Location: " & location)
```

### 方法5：組合使用`+`或`&`和`Console.Write()`
您還可以使用`Console.Write()`在不自動添加換行符的情況下逐個輸出變量，然後最後使用`Console.WriteLine()`添加一個換行。

```vb
Dim name As String = "David"
Dim age As Integer = 30
Dim location As String = "Taiwan"

Console.Write("Name: " & name & ", ")
Console.Write("Age: " & age.ToString() & ", ")
Console.WriteLine("Location: " & location)
```

這些方法中的每一種都有其適用場景，您可以根據具體需求選擇最適合的一種或者結合使用它們。