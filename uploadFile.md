要在ASP.NET MVC中使用VBHTML檔案和Controller來實作一個上傳檔案的功能，你可以依照以下步驟操作：

### 1. 建立一個新的ASP.NET MVC專案
在Visual Studio中，選擇「File」>「New」>「Project」，然後選擇「ASP.NET Web Application」。確保選擇「MVC」並且在程式語言中選擇Visual Basic。

### 2. 增加一個Model
在`Models`資料夾中，新增一個VB檔案用來定義上傳檔案的資料結構。例如，你可以建立一個`FileUpload.vb`檔案，並增加以下的程式碼：

```vb
Public Class FileUpload
    Public Property File As HttpPostedFileBase
End Class
```

### 3. 建立一個Controller
在`Controllers`資料夾中，新增一個名為`FileUploadController.vb`的Controller檔案。增加兩個Action，一個用於顯示上傳表單，另一個用於處理檔案上傳。

```vb
Imports System.Web.Mvc

Namespace Controllers
    Public Class FileUploadController
        Inherits Controller

        ' GET: FileUpload
        Function Index() As ActionResult
            Return View()
        End Function

        ' POST: FileUpload
        <HttpPost>
        Function Index(ByVal model As FileUpload) As ActionResult
            If ModelState.IsValid AndAlso model.File IsNot Nothing AndAlso model.File.ContentLength > 0 Then
                Dim fileName As String = System.IO.Path.GetFileName(model.File.FileName)
                Dim uploadPath As String = Server.MapPath("~/App_Data/uploads")
                model.File.SaveAs(System.IO.Path.Combine(uploadPath, fileName))
                ViewBag.Message = "File uploaded successfully."
            End If

            Return View(model)
        End Function
    End Class
End Namespace
```

### 4. 建立一個View
在`Views/FileUpload`資料夾中（如果不存在，請自行建立），新增一個名為`Index.vbhtml`的檔案。增加以下的程式碼來建立一個簡單的檔案上傳表單：

```vbhtml
@ModelType YourProjectName.Models.FileUpload

@<form action="" method="post" enctype="multipart/form-data">
    @Html.AntiForgeryToken()
    
    <label for="file">Choose file to upload:</label>
    <input type="file" name="file" id="file" />
    <input type="submit" value="Upload" />
    @If ViewBag.Message IsNot Nothing Then
        <p>@ViewBag.Message</p>
    End If
</form>
```

### 5. 測試上傳功能
現在，當你運行應用程式並導航到 `/FileUpload` ，你應該會看到一個檔案上傳表單。試著上傳一個檔案，並確認它是否被儲存到了`App_Data/uploads`資料夾中。

以上就是使用VBHTML和Controller在ASP.NET MVC中實作檔案上傳功能的基本步驟。如果有任何疑問或需要進一步的協助，請隨時詢問！


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