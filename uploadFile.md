了解，以下是如何使用 VBHTML 和控制器（Controller）來實現一個可以上傳多個文件到特定資料夾的 ASP.NET MVC 範例。

### 步驟 1: 設置專案

1. 在 Visual Studio 中建立一個新的 ASP.NET MVC 專案。
2. 安裝 Bootstrap，可以使用 CDN 或本地文件。

### 步驟 2: 引入 Bootstrap

在 `Views/Shared/_Layout.vbhtml` 中引入 Bootstrap：

```vbhtml
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>@ViewBag.Title - My ASP.NET Application</title>
    <link href="https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css" rel="stylesheet" />
</head>
<body>
    <div class="container">
        @RenderBody()
    </div>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.16.0/umd/popper.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js"></script>
</body>
</html>
```

### 步驟 3: 設計上傳表單

在 `Views/Home/Index.vbhtml` 中設計上傳表單：

```vbhtml
@{
    ViewBag.Title = "文件上傳";
}

<div class="container">
    <h2>文件上傳</h2>
    @Using Html.BeginForm("UploadFiles", "Home", FormMethod.Post, New With {.enctype = "multipart/form-data"})
        <div class="form-group">
            <label for="fileUpload">選擇文件：</label>
            <input type="file" id="fileUpload" name="files" multiple class="form-control" />
        </div>
        <div class="form-group">
            <input type="submit" value="上傳" class="btn btn-primary" />
        </div>
    End Using
    @If TempData("Message") IsNot Nothing Then
        <div class="alert alert-info mt-3">
            @TempData("Message")
        </div>
    End If
</div>
```

### 步驟 4: 建立控制器

在 `Controllers` 資料夾中建立 `HomeController.vb`，並撰寫處理上傳邏輯的控制器動作：

```vb
Imports System.IO
Imports System.Web.Mvc

Public Class HomeController
    Inherits Controller

    ' GET: Home
    Function Index() As ActionResult
        Return View()
    End Function

    <HttpPost>
    Function UploadFiles(files As IEnumerable(Of HttpPostedFileBase)) As ActionResult
        If files IsNot Nothing AndAlso files.Any(Function(f) f IsNot Nothing AndAlso f.ContentLength > 0) Then
            Dim uploadPath As String = Server.MapPath("~/Uploads/")
            If Not Directory.Exists(uploadPath) Then
                Directory.CreateDirectory(uploadPath)
            End If

            For Each file As HttpPostedFileBase In files
                If file IsNot Nothing AndAlso file.ContentLength > 0 Then
                    Dim filePath As String = Path.Combine(uploadPath, Path.GetFileName(file.FileName))
                    file.SaveAs(filePath)
                End If
            Next

            TempData("Message") = "文件上傳成功！"
        Else
            TempData("Message") = "請選擇至少一個文件進行上傳。"
        End If

        Return RedirectToAction("Index")
    End Function
End Class
```

### 完整範例代碼

#### Views/Shared/_Layout.vbhtml

```vbhtml
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>@ViewBag.Title - My ASP.NET Application</title>
    <link href="https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css" rel="stylesheet" />
</head>
<body>
    <div class="container">
        @RenderBody()
    </div>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.16.0/umd/popper.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js"></script>
</body>
</html>
```

#### Views/Home/Index.vbhtml

```vbhtml
@{
    ViewBag.Title = "文件上傳";
}

<div class="container">
    <h2>文件上傳</h2>
    @Using Html.BeginForm("UploadFiles", "Home", FormMethod.Post, New With {.enctype = "multipart/form-data"})
        <div class="form-group">
            <label for="fileUpload">選擇文件：</label>
            <input type="file" id="fileUpload" name="files" multiple class="form-control" />
        </div>
        <div class="form-group">
            <input type="submit" value="上傳" class="btn btn-primary" />
        </div>
    End Using
    @If TempData("Message") IsNot Nothing Then
        <div class="alert alert-info mt-3">
            @TempData("Message")
        </div>
    End If
</div>
```

#### Controllers/HomeController.vb

```vb
Imports System.IO
Imports System.Web.Mvc

Public Class HomeController
    Inherits Controller

    ' GET: Home
    Function Index() As ActionResult
        Return View()
    End Function

    <HttpPost>
    Function UploadFiles(files As IEnumerable(Of HttpPostedFileBase)) As ActionResult
        If files IsNot Nothing AndAlso files.Any(Function(f) f IsNot Nothing AndAlso f.ContentLength > 0) Then
            Dim uploadPath As String = Server.MapPath("~/Uploads/")
            If Not Directory.Exists(uploadPath) Then
                Directory.CreateDirectory(uploadPath)
            End If

            For Each file As HttpPostedFileBase In files
                If file IsNot Nothing AndAlso file.ContentLength > 0 Then
                    Dim filePath As String = Path.Combine(uploadPath, Path.GetFileName(file.FileName))
                    file.SaveAs(filePath)
                End If
            Next

            TempData("Message") = "文件上傳成功！"
        Else
            TempData("Message") = "請選擇至少一個文件進行上傳。"
        End If

        Return RedirectToAction("Index")
    End Function
End Class
```

這樣你就完成了一個可以上傳多個文件至特定資料夾的 ASP.NET MVC 應用程式。希望這些步驟對你有幫助！