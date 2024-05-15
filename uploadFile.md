若您希望在用户上传文件之前能够预览文件名列表，并在用户确认后才真正上传文件，我们可以采用JavaScript来实现这个预览功能，并使用一个简单的表单来上传文件。以下是如何实现这一功能的步骤：

### 1. 修改视图文件以添加预览功能

您可以在`Index.vbhtml`视图文件中添加JavaScript代码来处理文件选择事件，捕捉选中的文件名，并在用户点击上传按钮之前显示这些文件名。

```vbhtml
@ModelType YourProjectName.Models.FileUpload

@<form id="uploadForm" action="@Url.Action("Index", "FileUpload")" method="post" enctype="multipart/form-data">
    @Html.AntiForgeryToken()
    <div class="form-group">
        <label for="files">Choose files to upload:</label>
        <input type="file" class="form-control" name="files" id="files" multiple onchange="previewFiles()" />
    </div>
    <div id="fileList" class="form-group">
        <!-- 预览文件名将在这里显示 -->
    </div>
    <button type="submit" class="btn btn-success" disabled="disabled" id="submitBtn">Upload</button>
</form>

<script>
function previewFiles() {
    var input = document.getElementById('files');
    var output = document.getElementById('fileList');
    var submitBtn = document.getElementById('submitBtn');

    output.innerHTML = '';
    if (input.files.length > 0) {
        var ul = document.createElement('ul');
        for (var i = 0; i < input.files.length; i++) {
            var li = document.createElement('li');
            li.textContent = input.files[i].name;
            ul.appendChild(li);
        }
        output.appendChild(ul);
        submitBtn.disabled = false; // Enable the submit button
    } else {
        submitBtn.disabled = true; // Disable the submit button if no files are selected
    }
}
</script>
```

### 2. 修改Controller来处理文件上传

确保`FileUploadController`的`Index`方法可以处理POST请求并保存上传的文件，如之前步骤所述。

### 3. 测试功能

启动您的应用程序，并尝试选择一些文件。文件名应该在您选择文件后立即显示在表单下方的列表中。您可以查看文件名并决定是否上传。

### 4. 样式调整

您可以使用Bootstrap或其他CSS框架来美化表单和文件列表的样式，确保它们符合您网站的整体风格。

通过这种方式，用户可以在文件上传前预览即将上传的文件名，并在确认无误后通过点击“Upload”按钮上传文件。这样的功能可以提升用户体验，确保文件上传前的透明度和可控性。如果您有任何疑问或需要进一步的帮助，请随时询问！

要在ASP.NET MVC应用中显示用户上传的文件列表，我们可以在上传文件后将文件名存储在视图模型中，并在模态窗口中显示这些文件名。以下是逐步指导如何实现这一功能：

### 1. 修改Model以存储文件名

首先，我们需要在`FileUpload`模型中添加一个字符串列表来存储上传文件的名称。

```vb
Public Class FileUpload
    Public Property Files As IEnumerable(Of HttpPostedFileBase)
    Public Property UploadedFileNames As List(Of String) = New List(Of String)()
End Class
```

### 2. 修改Controller以更新文件名列表

在`FileUploadController`的上传方法中，我们需要更新模型，将上传的文件名添加到列表中。

```vb
Imports System.Web.Mvc

Namespace Controllers
    Public Class FileUploadController
        Inherits Controller

        ' GET: FileUpload
        Function Index() As ActionResult
            Return View(New FileUpload())
        End Function

        ' POST: FileUpload
        <HttpPost>
        Function Index(ByVal model As FileUpload) As ActionResult
            If ModelState.IsValid AndAlso model.Files IsNot Nothing AndAlso model.Files.Any() Then
                For Each file In model.Files
                    If file IsNot Nothing AndAlso file.ContentLength > 0 Then
                        Dim fileName As String = System.IO.Path.GetFileName(file.FileName)
                        Dim uploadPath As String = Server.MapPath("~/App_Data/uploads")
                        file.SaveAs(System.IO.Path.Combine(uploadPath, fileName))
                        model.UploadedFileNames.Add(fileName)
                    End If
                Next
                ViewBag.Message = "Files uploaded successfully."
            End If

            Return View(model)
        End Function
    End Class
End Namespace
```

### 3. 修改视图以显示上传的文件名

在模态窗口的视图中，我们需要添加一个部分来显示上传的文件名。

```vbhtml
<div class="modal-body">
    @Html.Partial("UploadForm", Model)
    
    @If Model.UploadedFileNames.Any() Then
        <div class="alert alert-info">
            <strong>Uploaded Files:</strong>
            <ul>
                @For Each fileName In Model.UploadedFileNames
                    @<li>@fileName</li>
                Next
            </ul>
        </div>
    End If
</div>
```

### 4. 确保部分视图使用模型

修改部分视图 `_UploadForm.vbhtml` 以确保它使用了从控制器传递的模型。

```vbhtml
@ModelType YourProjectName.Models.FileUpload

@<form action="@Url.Action("Index", "FileUpload")" method="post" enctype="multipart/form-data">
    @Html.AntiForgeryToken()
    <div class="form-group">
        <label>Choose files to upload:</label>
        <input type="file" class="form-control" name="files" multiple />
    </div>
    <button type="submit" class="btn btn-success">Upload</button>
</form>
```

### 5. 测试功能

现在运行您的应用程序，尝试上传文件，并检查模态窗口中是否正确显示了文件名列表。

这样，您就可以在模态窗口中实现一个文件上传功能，并显示已上传的文件名列表，以便用户能够看到他们已经上传了哪些文件。如果有任何问题或需要进一步的帮助，请随时询问！

要在你的ASP.NET MVC應用中整合Bootstrap，你可以通過以下步驟來美化和增強你的檔案上傳表單的外觀和感覺。

### 1. 安裝Bootstrap
首先，你需要將Bootstrap添加到你的專案中。在Visual Studio中，你可以使用NuGet包管理器來安裝Bootstrap。

- 打開你的專案，點擊「Tools」>「NuGet Package Manager」>「Manage NuGet Packages for Solution」。
- 搜索「Bootstrap」，選擇相應的Bootstrap套件（如`bootstrap`）並安裝到你的專案中。

### 2. 修改_Layout.vbhtml以引入Bootstrap
在`Views/Shared`資料夾中找到`_Layout.vbhtml`檔案，並確保在`<head>`區塊中添加了Bootstrap的CSS引用，以及在`<body>`標籤末尾添加了JavaScript引用。

```html
<link href="~/Content/bootstrap.min.css" rel="stylesheet" type="text/css" />
<script src="~/Scripts/jquery-3.3.1.min.js"></script>
<script src="~/Scripts/bootstrap.min.js"></script>
```

### 3. 使用Bootstrap更新你的View
更新`Views/FileUpload/Index.vbhtml`，使用Bootstrap的CSS類來美化表單。

```vbhtml
@ModelType YourProjectName.Models.FileUpload

@<form action="" method="post" enctype="multipart/form-data" class="form-horizontal">
    @Html.AntiForgeryToken()

    <div class="form-group">
        <label for="file" class="col-md-2 control-label">Choose files to upload:</label>
        <div class="col-md-10">
            <input type="file" class="form-control" name="files" id="file" multiple="multiple" />
        </div>
    </div>
    <div class="form-group">
        <div class="col-md-offset-2 col-md-10">
            <input type="submit" value="Upload" class="btn btn-primary" />
        </div>
    </div>
    @If ViewBag.Message IsNot Nothing Then
        <div class="alert alert-success">
            <p>@ViewBag.Message</p>
        </div>
    End If
</form>
```

這裡我們使用了`form-horizontal`類來使表單水平對齊，並使用了`form-group`和`control-label`來結構化每個輸入元素。`btn btn-primary`使提交按鈕看起來更漂亮。

### 4. 測試並調整
現在運行你的ASP.NET MVC應用，並導航到`/FileUpload`。你應該會看到一個使用Bootstrap風格的表單。你可以根據需要進行進一步的美化和調整。

以上步驟將引

要實作多檔案上傳功能，你需要對Model和View做一些調整，使其可以接受和處理多個檔案。下面是步驟的詳細說明：

### 1. 修改Model
在`FileUpload.vb`中，將`File`屬性從單一檔案改為檔案列表。

```vb
Public Class FileUpload
    Public Property Files As IEnumerable(Of HttpPostedFileBase)
End Class
```

### 2. 修改Controller
更新`FileUploadController.vb`中的`Index`方法，讓它能處理多個檔案的上傳。

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
            If ModelState.IsValid AndAlso model.Files IsNot Nothing AndAlso model.Files.Any() Then
                For Each file In model.Files
                    If file IsNot Nothing AndAlso file.ContentLength > 0 Then
                        Dim fileName As String = System.IO.Path.GetFileName(file.FileName)
                        Dim uploadPath As String = Server.MapPath("~/App_Data/uploads")
                        file.SaveAs(System.IO.Path.Combine(uploadPath, fileName))
                    End If
                Next
                ViewBag.Message = "Files uploaded successfully."
            End If

            Return View(model)
        End Function
    End Class
End Namespace
```

### 3. 修改View
在`Index.vbhtml`中，更新表單以允許選擇多個檔案。

```vbhtml
@ModelType YourProjectName.Models.FileUpload

@<form action="" method="post" enctype="multipart/form-data">
    @Html.AntiForgeryToken()

    <label for="file">Choose files to upload:</label>
    <input type="file" name="files" id="file" multiple="multiple" />
    <input type="submit" value="Upload" />
    @If ViewBag.Message IsNot Nothing Then
        <p>@ViewBag.Message</p>
    End If
</form>
```

在`<input type="file"`標籤中，添加`multiple="multiple"`屬性，這樣使用者就可以選擇多個檔案來上傳。注意表單中`name`屬性的值是`files`，這需要與Model中定義的屬性相對應。

### 4. 測試功能
運行你的ASP.NET MVC應用程式，並導航到 `/FileUpload`。你應該可以選擇多個檔案進行上傳。上傳完成後，檢查`App_Data/uploads`資料夾以確認檔案是否正確上傳。

這樣就完成了ASP.NET MVC應用中的多檔案上傳功能的實作。如果你有進一步的問題或需要更多的幫助，請隨時提問！


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