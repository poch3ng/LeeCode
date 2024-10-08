當視窗縮小時，按鈕疊在一起通常是因為按鈕的容器沒有足夠的空間讓按鈕水平排列。為了解決這個問題，我們可以讓按鈕在視窗變小的時候自動進行垂直排列，或調整它們的間距，確保它們不會重疊。

### 解決方案：
1. **使用 `Flexbox`**：讓按鈕在寬度不足時自動換行或改變排列方向。
2. **使用 `Media Queries`**：當視窗變小時，動態調整按鈕排列方式，例如在小螢幕下將按鈕垂直排列。

### 修改方式：

#### 1. **讓按鈕在寬度不足時自動換行**
   這可以通過 `flex-wrap: wrap` 來實現。當空間不足時，按鈕會自動換行。

```css
.button-container {
    position: absolute;
    top: 70%; /* 按鈕容器的位置，根據需要調整 */
    left: 25%; /* 從左邊過來 25% */
    display: flex;
    gap: 20px; /* 按鈕之間的間距 */
    flex-wrap: wrap; /* 當按鈕無法水平排列時自動換行 */
    transform: translateY(-50%);
}
```

#### 2. **使用 `Media Queries` 進行響應式設計**
   當螢幕縮小時，可以通過 `Media Queries` 將按鈕從水平排列改為垂直排列，這樣它們就不會重疊。

```css
@media screen and (max-width: 768px) {
    .button-container {
        flex-direction: column; /* 在小螢幕上按鈕垂直排列 */
        left: 10%; /* 根據螢幕大小調整按鈕的位置 */
        top: 80%; /* 按鈕容器在小螢幕下的位置調整 */
    }

    .custom-link {
        width: auto; /* 保證按鈕的寬度自適應 */
        font-size: 14px; /* 調整字體大小 */
        padding: 8px 16px; /* 調整按鈕的內邊距 */
    }
}
```

#### 3. **完整範例**

```css
.image-container {
    position: relative; /* 設置容器為相對定位，方便按鈕絕對定位 */
    width: 100%;
    max-width: 1920px; /* 確保圖片寬度不超過原始大小 */
    height: 159px;     /* 固定高度，與圖片一致 */
}

.background-image {
    width: 100%;
    height: 100%;
    background-image: url('your-image.jpg');
    background-size: cover; /* 確保圖片完全覆蓋容器 */
    background-position: center;
    background-repeat: no-repeat;
}

.button-container {
    position: absolute;
    top: 70%; /* 將按鈕容器位置調整到圖片的 70% 高度處 */
    left: 25%; /* 從左邊過來 25% */
    display: flex;
    gap: 20px; /* 按鈕之間的間距 */
    flex-wrap: wrap; /* 當按鈕無法水平排列時自動換行 */
    transform: translateY(-50%);
}

.custom-link {
    padding: 10px 20px;
    background-color: rgba(255, 255, 255, 0.8); /* 背景色稍微透明，讓按鈕與圖片區分 */
    border: 1px solid #ccc;
    text-decoration: none;
    color: #000;
    font-size: 16px;
    cursor: pointer;
}

/* 小螢幕響應式調整 */
@media screen and (max-width: 768px) {
    .button-container {
        flex-direction: column; /* 在小螢幕上按鈕垂直排列 */
        left: 10%; /* 調整左邊距，讓按鈕容器在小螢幕上更居中 */
        top: 80%;  /* 調整按鈕容器的垂直位置 */
    }

    .custom-link {
        width: auto; /* 保證按鈕的寬度自適應 */
        font-size: 14px; /* 調整字體大小 */
        padding: 8px 16px; /* 調整按鈕的內邊距 */
    }
}
```

### 這樣的解決方案：
1. **自動換行**：當螢幕寬度不足時，按鈕會自動換行，避免重疊。
2. **響應式布局**：在較小螢幕下（例如手機或平板設備上），按鈕會垂直排列，並根據螢幕大小自動調整位置和大小。
3. **按鈕樣式調整**：在小螢幕上，按鈕會自動縮小並適應視窗大小。

這樣可以確保按鈕在不同螢幕尺寸下都不會重疊，並保持清晰的顯示效果。
如果圖片是固定大小的 1920x159，並且在頁面顯示時下方有空白，這通常是因為圖片的寬度佔滿了頁面寬度，但圖片高度固定，導致在圖片下方出現了多餘的空白區域。要解決這個問題，你可以使用以下幾種方法來調整圖片的顯示方式，使其適應頁面的大小，而不會在下方產生空白。

### 1. **設置圖片容器的背景圖片**

如果你希望圖片自適應寬度並避免下方的空白，最好的解決方案是將圖片設為容器的背景圖片，並使用 `background-size: cover` 或 `background-size: contain` 來控制其顯示效果。這樣圖片會根據容器的大小自動調整，避免空白出現。

#### 具體步驟：

### HTML
將圖片設置為容器的背景，而不是直接使用 `<img>` 標籤。

```html
<div class="image-container">
    <div class="background-image">
        <!-- 按鈕直接放在背景圖片上 -->
        <div class="button-container">
            <asp:LinkButton ID="LinkButton1" runat="server" CssClass="custom-link">Link 1</asp:LinkButton>
            <asp:LinkButton ID="LinkButton2" runat="server" CssClass="custom-link">Link 2</asp:LinkButton>
        </div>
    </div>
</div>
```

### CSS
使用 `background-image` 設置圖片，並使用 `background-size: cover` 來確保圖片會自動調整以適應容器的大小。

```css
.image-container {
    width: 100%;
    height: 159px; /* 固定高度，與圖片一致 */
    position: relative;
}

.background-image {
    width: 100%;
    height: 100%;
    background-image: url('your-image.jpg');
    background-size: cover; /* 確保圖片完全覆蓋容器 */
    background-position: center; /* 圖片居中 */
    background-repeat: no-repeat; /* 避免重複顯示圖片 */
}

.button-container {
    position: absolute;
    top: 50%;
    left: 25%;
    display: flex;
    gap: 20px;
    transform: translateY(-50%);
}

.custom-link {
    padding: 10px 20px;
    background-color: rgba(255, 255, 255, 0.8);
    border: 1px solid #ccc;
    text-decoration: none;
    color: #000;
    font-size: 16px;
    cursor: pointer;
}
```

### 2. **使用 `img` 並設置圖片高度為 `auto`**
如果你仍然希望使用 `<img>` 元素而不是背景圖片，那麼可以通過設置圖片的高度為自動 (`height: auto`) 來確保圖片保持比例，不會導致下方出現多餘的空白。這樣，圖片會根據其內容進行調整。

#### 修改 CSS 如下：
```css
.image-container {
    width: 100%;
    max-width: 1920px; /* 確保圖片不超過原始寬度 */
    height: 159px; /* 固定高度 */
    position: relative;
    overflow: hidden; /* 避免內容超出容器邊界 */
}

.background-image {
    width: 100%;
    height: auto; /* 自動調整高度，保持圖片比例 */
    display: block; /* 消除圖片周圍的空白 */
}

.button-container {
    position: absolute;
    top: 50%;
    left: 25%;
    display: flex;
    gap: 20px;
    transform: translateY(-50%);
}

.custom-link {
    padding: 10px 20px;
    background-color: rgba(255, 255, 255, 0.8);
    border: 1px solid #ccc;
    text-decoration: none;
    color: #000;
    font-size: 16px;
    cursor: pointer;
}
```

### 3. **設置 `object-fit`（如果使用 `<img>` 標籤）**
你也可以使用 `object-fit` 屬性來調整圖片的顯示，確保圖片按照需要自動縮放。這樣可以避免圖片下方產生空白。

#### 修改 `img` 標籤：
```css
.background-image {
    width: 100%;
    height: 159px; /* 固定高度 */
    object-fit: cover; /* 圖片會自動縮放並覆蓋容器 */
    display: block;
}
```

### 總結：
1. **背景圖片解決方案**：使用 `background-image` 並設置 `background-size: cover`，確保圖片覆蓋容器且不會產生空白。
2. **`img` 元素方案**：使用 `height: auto` 讓圖片保持比例並自動調整高度，或使用 `object-fit: cover` 來確保圖片適應容器大小。
3. **響應式設計**：無論使用哪種方法，都應考慮圖片的響應式布局，確保在不同的螢幕大小下顯示正常，避免出現空白區域。

這些方法能確保圖片與按鈕能動態適應頁面，且不會在圖片下方產生空白。

要實現 `LinkButton` 重疊在圖片上，且位置能根據圖片的大小動態調整，你可以使用 `position: absolute` 和 `position: relative` 來實現這種效果。這樣，按鈕會疊加在圖片上，並且隨著圖片的大小進行相應的變化。

### 具體步驟如下：

### 1. **HTML 結構**
你可以使用 `div` 容器來包裹圖片和按鈕，並且確保這個 `div` 使用相對定位 (`position: relative`)。這樣，按鈕就可以通過絕對定位 (`position: absolute`) 來相對於圖片進行定位。

```html
<div class="image-container">
    <img src="your-image.jpg" alt="Background Image" class="background-image" />
    
    <!-- LinkButton 1 -->
    <asp:LinkButton ID="LinkButton1" runat="server" CssClass="custom-link">Link 1</asp:LinkButton>
    
    <!-- LinkButton 2 -->
    <asp:LinkButton ID="LinkButton2" runat="server" CssClass="custom-link">Link 2</asp:LinkButton>
</div>
```

### 2. **CSS 設定**

你需要設定圖片和按鈕的樣式，使用 `position: absolute` 將按鈕疊加在圖片上。可以使用百分比來確定按鈕在圖片上的位置，這樣可以實現動態調整。

```css
.image-container {
    position: relative;
    width: 100%;   /* 圖片容器的寬度設置為100% */
    max-width: 1897px; /* 確保圖片不會超過其原始寬度 */
    height: auto;  /* 高度自動調整，保持圖片的比例 */
}

.background-image {
    width: 100%;   /* 圖片寬度佔滿容器 */
    height: auto;  /* 保持圖片比例 */
}

.custom-link {
    position: absolute;
    top: 50%;        /* 按鈕垂直位置設置在圖片高度的 50% */
    left: 25%;       /* 按鈕水平位置設置在圖片寬度的 25% (即1/4處) */
    transform: translate(-50%, -50%); /* 使按鈕的中心點對齊定位點 */
    padding: 10px 20px;
    background-color: rgba(255, 255, 255, 0.8); /* 背景色稍微透明，讓按鈕與圖片區分 */
    border: 1px solid #ccc;
    text-decoration: none;
    color: #000;
    font-size: 16px;
    cursor: pointer;
}

.custom-link + .custom-link {
    top: 60%;  /* 第二個按鈕的位置，稍微下移 */
}
```

### 3. **按鈕在圖片上動態調整位置**
使用百分比 (`left: 25%`、`top: 50%`) 來控制按鈕的位置，這樣當圖片縮放時，按鈕的位置也會相應調整。另外，通過 `transform: translate(-50%, -50%)` 將按鈕的中心對齊你指定的定位點，使按鈕更加精確地定位在圖片上。

### 4. **響應式布局（可選）**

如果需要根據不同裝置大小進行進一步調整，可以使用 Media Queries 來實現響應式布局。

```css
@media screen and (max-width: 768px) {
    .custom-link {
        font-size: 14px; /* 調整字體大小 */
        padding: 8px 16px; /* 調整按鈕大小 */
    }
}
```

### 最終效果：
- 圖片和按鈕會動態調整大小，當圖片變大或變小時，按鈕的位置也會根據圖片的比例自動調整。
- 按鈕會重疊在圖片上，並且根據你指定的位置顯示在圖片的左側 1/4 和中央（或其他你定義的位置）。

### 總結：
- 使用 `position: absolute` 將按鈕疊加在圖片上。
- 使用百分比 (`left` 和 `top`) 來動態控制按鈕的位置，使其隨著圖片大小的變化進行調整。
- 確保圖片和容器的寬度和高度是響應式的 (`width: 100%` 和 `height: auto`)。

這樣就可以實現按鈕重疊在圖片上，並且位置會隨著圖片大小動態調整。

要讓兩個 `LinkButton` 在圖片上動態顯示位置（例如根據螢幕大小或圖片大小自動調整），可以使用百分比布局或 CSS Flexbox/Grid 等響應式技術，這樣不管圖片的大小或螢幕的寬度如何改變，按鈕的位置都能自動調整。

以下是實現動態布局的方法：

### 1. **HTML 結構**
仍然保持圖片和 `LinkButton` 放在同一個容器中，並使用 `position: relative` 和 `position: absolute` 來進行定位。

```html
<div class="image-container">
    <img src="your-image.jpg" alt="Background Image" class="background-image" />
    
    <!-- LinkButton 1 -->
    <asp:LinkButton ID="LinkButton1" runat="server" CssClass="custom-link">Link 1</asp:LinkButton>
    
    <!-- LinkButton 2 -->
    <asp:LinkButton ID="LinkButton2" runat="server" CssClass="custom-link">Link 2</asp:LinkButton>
</div>
```

### 2. **動態 CSS 設置**

使用百分比來控制 `LinkButton` 的位置和大小，使其隨著圖片和螢幕的大小自動調整。

```css
.image-container {
    position: relative;
    width: 100%;    /* 圖片容器佔滿父級寬度，保持響應式 */
    max-width: 100%; /* 確保容器不會超過原始圖片的寬度 */
    height: auto;    /* 高度自動調整 */
}

.background-image {
    width: 100%;
    height: auto;    /* 圖片高度根據寬度自動調整 */
}

.custom-link {
    position: absolute;
    top: 50%;        /* 按鈕的垂直位置：圖片高度的 50% */
    left: 25%;       /* 從左邊過來 1/4 的位置 */
    transform: translate(-50%, -50%); /* 讓按鈕居中 */
    padding: 1% 2%;  /* 按鈕的 padding 根據容器大小進行調整 */
    background-color: rgba(255, 255, 255, 0.8); /* 半透明背景 */
    border: 1px solid #ccc;
    text-decoration: none;
    color: #000;
    font-size: 1.5vw; /* 使用 vw（視窗寬度）作為字體大小的單位 */
    cursor: pointer;
}

.custom-link + .custom-link {
    top: 60%;  /* 第二個按鈕比第一個按鈕稍微下移 */
}
```

### 解釋：
1. **`.image-container`**：容器的寬度設置為 `100%`，這樣可以隨螢幕大小自適應。高度設置為 `auto` 讓圖片能夠等比縮放。
2. **`.background-image`**：圖片的寬度設置為 `100%`，使其隨容器大小自動縮放。高度設置為 `auto` 確保圖片不會變形。
3. **`.custom-link`**：按鈕的位置使用百分比來定位（`left: 25%` 表示從左邊過來四分之一處）。按鈕的字體大小使用 `vw`（視窗寬度單位），確保字體大小隨著視窗的大小動態調整。`transform: translate(-50%, -50%)` 用來讓按鈕在 `top` 和 `left` 的位置居中顯示。
4. **`padding` 和 `font-size`**：按鈕的 `padding` 和 `font-size` 使用百分比或視窗寬度來設置，這樣按鈕的大小和字體會根據螢幕大小進行調整。

### 3. **使用 Media Queries（可選）**
如果希望在不同螢幕大小下有不同的排版效果，可以使用 Media Queries 來做進一步的響應式調整。

```css
@media screen and (max-width: 768px) {
    .custom-link {
        font-size: 3vw; /* 在小螢幕上字體變大 */
        padding: 2% 4%; /* 小螢幕按鈕的 padding 也增大 */
    }
}
```

### 最終效果：
這樣，無論圖片的大小怎麼變化，按鈕的位置和大小都會自動根據圖片大小和螢幕寬度進行調整，從而實現動態的效果。

### 總結：
- 使用百分比來設置按鈕的位置 (`left: 25%`) 和大小 (`font-size`、`padding`)。
- 確保容器和圖片都是響應式的，通過 `width: 100%` 和 `height: auto` 保持圖片等比縮放。
- 如果需要在不同螢幕大小下進行微調，可以使用 Media Queries。

要在一張 1897x159 的圖片上，從左邊過來 1/4 的位置放置兩個 `LinkButton`，可以使用 CSS 結合絕對定位來實現。以下是具體步驟：

### 1. **HTML 結構**
   在你的頁面上放置圖片和兩個 `LinkButton`，使用一個 `div` 來作為容器，並且為 `LinkButton` 設置絕對定位。

### 2. **CSS 絕對定位**
   使用 CSS 的 `position: absolute` 來控制 `LinkButton` 的位置，並將它們放在圖片上從左邊過來 1/4 的位置。

### 具體範例：

```html
<div class="image-container">
    <img src="your-image.jpg" alt="Background Image" class="background-image" />
    
    <!-- LinkButton 1 -->
    <asp:LinkButton ID="LinkButton1" runat="server" CssClass="custom-link">Link 1</asp:LinkButton>
    
    <!-- LinkButton 2 -->
    <asp:LinkButton ID="LinkButton2" runat="server" CssClass="custom-link">Link 2</asp:LinkButton>
</div>
```

### 3. **CSS 定義**

```css
.image-container {
    position: relative;
    width: 1897px;
    height: 159px;
}

.background-image {
    width: 100%;
    height: 100%;
}

.custom-link {
    position: absolute;
    top: 50%; /* 垂直居中 */
    left: 25%; /* 從左邊 1/4 處開始 */
    transform: translateY(-50%); /* 垂直方向修正位置居中 */
    padding: 10px 20px;
    background-color: rgba(255, 255, 255, 0.8); /* 背景色，便於按鈕可見 */
    border: 1px solid #ccc;
    text-decoration: none;
    color: #000;
    font-size: 16px;
    cursor: pointer;
}

.custom-link + .custom-link {
    top: 60%; /* 第二個按鈕距離第一個按鈕稍微下移 */
}
```

### 解釋：
1. **`.image-container`**：用來容納圖片和按鈕，設置 `position: relative`，以便按鈕能夠根據容器進行定位。
2. **`.background-image`**：背景圖片，設定為寬度 100% 並根據容器的大小調整高度。
3. **`.custom-link`**：按鈕的樣式，使用 `position: absolute` 定位，設定在圖片容器內從左邊過來 25%（即 1/4 位置）。`top: 50%` 將按鈕垂直居中，`transform: translateY(-50%)` 確保按鈕的垂直居中效果。
4. **第二個按鈕的位置**：使用 `.custom-link + .custom-link` 選擇第二個 `LinkButton`，並設置它的位置比第一個稍微下移。

### 最終效果：
這樣你就可以在圖片的左邊 1/4 的位置放置兩個 `LinkButton`，並且它們將按照你設置的樣式顯示。你可以根據需要進一步調整按鈕的位置、間距和樣式。

