要在UiPath中使用「Send SMTP Mail Message」活動來嵌入一個PNG圖檔到電子郵件正文中，你可以按照以下步驟進行操作：

### 步驟一：準備PNG圖檔
確保你的PNG圖檔已經準備好，並知道它的完整路徑。例如：`C:\Images\example.png`。

### 步驟二：建立郵件內容
1. 在「Send SMTP Mail Message」活動的「Body」屬性中撰寫HTML內容，並使用`<img>`標籤嵌入圖檔。`src`屬性使用`cid`來表示附件中的圖檔。範例如下：
   ```html
   <html>
       <body>
           <p>您好，</p>
           <p>請查看下方的圖片：</p>
           <img src='cid:image1' alt='Image'/>
       </body>
   </html>
   ```

### 步驟三：添加附件
1. 在「Send SMTP Mail Message」活動的「Attachments」屬性中，使用變量來添加PNG圖檔。例如：
   ```vb
   New System.Net.Mail.Attachment("C:\Images\example.png")
   ```
2. 此外，需要設定該附件的`ContentId`屬性來對應HTML中的`cid:image1`。

### 步驟四：設置 Content-ID
使用「Invoke Method」活動來設置圖檔的`ContentId`，具體步驟如下：
1. 在「Attachments」屬性中保存附件為變量，比如`pngAttachment`。
2. 在工作流程中添加「Invoke Method」活動。
   - 目標物件設置為`pngAttachment.ContentId`。
   - 方法名稱設置為`SetValue`。
   - 設置方法參數：
     - 第一個參數為 `"image1"`（這與HTML中的`cid:image1`一致）。
     - 第二個參數為 `System.String`。

### 步驟五：發送郵件
確保SMTP的配置正確，運行流程，即可發送帶有嵌入PNG圖檔的電子郵件。

這樣收件人就能在郵件正文中直接看到圖片，而不是作為附件。