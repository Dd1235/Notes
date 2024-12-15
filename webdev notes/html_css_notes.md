# Notes on HTML and CSS

## HTML Basics

### Structure of HTML Documents

- **Body**: Contains the content that gets rendered in the browser window.

- **Head**: Includes metadata such as the document title, linked stylesheets, and scripts.

### Common Formatting Tags

- `<strong>`: Emphasizes text by making it bold.
  ```html
  <strong>Important Text</strong>
  ```

- `<em>`: Emphasizes text by italicizing it.
  ```html
  <em>Highlighted Text</em>
  ```

### List Elements

- **Unordered List** (`<ul>`): Displays a bullet-point list.
  ```html
  <ul>
      <li>First Item</li>
      <li>Second Item</li>
  </ul>
  ```

- **Ordered List** (`<ol>`): Displays a numbered list.
  ```html
  <ol>
      <li>Step One</li>
      <li>Step Two</li>
  </ol>
  ```

### Containers: Division and Span

- `<div>`: Defines a block-level section for grouping related content.
  ```html
  <div>
      <p>Section Content</p>
  </div>
  ```

- `<span>`: Defines an inline container, often used for styling specific parts of text.
  ```html
  <span class="highlight">Inline Highlight</span>
  ```

### Line and Content Separators

- `<br>`: Inserts a line break in the content.
  ```html
  First Line<br>Second Line
  ```

- `<hr>`: Adds a horizontal line to separate sections.
  ```html
  <hr>
  ```

### Images

- `<img>`: Embeds an image into the page. Requires `src` for the file path and `alt` for alternative text.
  ```html
  <img src="image.jpg" alt="Descriptive Text">
  ```

- Use absolute paths (`/`) for referencing files from the root directory.

### Hyperlinks

- `<a>`: Creates clickable links to other pages or external websites.
  ```html
  <a href="https://example.com">Visit Example</a>
  ```

- For local files:
  ```html
  <a href="file.html">Local File Link</a>
  ```

### Blockquote Element

- `<blockquote>`: Used for quoting longer text passages. Optionally includes a `cite` attribute for the source.
  ```html
  <blockquote cite="https://source.com">Quoted Text</blockquote>
  ```

---

## HTML Forms

### Form Basics

- `<form>`: Defines a form for user input. The `action` attribute specifies where the form data will be sent.
  ```html
  <form action="/submit">
      <!-- Input Elements -->
  </form>
  ```

### Labels and Input Fields

- **Label**: Associates descriptive text with an input field, enhancing accessibility.
  ```html
  <label for="username">Enter Username:</label>
  <input type="text" id="username" name="username" placeholder="Your Username">
  ```

### Input Types

- HTML provides various input types for forms, such as:
  - `text`, `email`, `password`
  - `date`, `number`, `range`
  - `search`, `tel`, `url`
  - `color`, `checkbox`, `radio`
  - `file`, `submit`, `reset`, `button`

- Example of an email input with a placeholder:
  ```html
  <input type="email" name="email" placeholder="Enter Your Email">
  ```

### Grouping Radio Buttons

- Use the `name` attribute to group related radio buttons so only one can be selected at a time.
  ```html
  <p>Select Your Gender:</p>
  <input type="radio" name="gender" value="male" id="male">
  <label for="male">Male</label><br>
  <input type="radio" name="gender" value="female" id="female">
  <label for="female">Female</label><br>
  <input type="radio" name="gender" value="other" id="other">
  <label for="other">Other</label><br>
  ```

- Another example for selecting age range:
  ```html
  <p>Select your age:</p>
  <input type="radio" name="age" value="0-25" id="option-1">
  <label for="option-1">0-25</label><br>
  <input type="radio" name="age" value="26-50" id="option-2">
  <label for="option-2">26-50</label><br>
  <input type="radio" name="age" value="51+" id="option-3">
  <label for="option-3">51+</label><br>
  ```

### Label Notes

- A `<label>` is linked to its input using the `for` attribute, but general descriptions for grouped inputs can use a `<p>` tag instead:
  ```html
  <p>Choose a category:</p>
  ```
- value attribute is for the server side developer
---

**Tip**: Use semantic HTML tags wherever possible and ensure attributes like `id`, `name`, and `placeholder` are consistent and meaningful.

### Select box

```html
<label for = "question"> Security question: </label>
<select name = "question" id = "question">
    <option value = "q1"> What is your mother's maiden name? </option>
    <option value = "q2"> What is the name of your first pet? </option>
    <option value = "q3"> What is your favorite color? </option>
</select>

<label for = "answer"> Security question Answer: </label>
<input type = "text" name = "answer" id = "answer">

<label for = "bio"> Bio: </label>
<textarea name = "bio" id = "bio" rows = "5" cols = "30" placeholder="enter..."></textarea> <!-- Can rewrite teh rows and cols using css, the area can be changed by the user -->

<input type = "submit" value = "submit the form, text user sees">
```

- add on a `required` attribute to make the field mandatory
- on submitting, the form data is sent to the server, and the page is reloaded, you will see all the data in the URL

---

### HTML 5 semantic tags

- <main> : the bit that is unique to that webpage
- <section> : section of a webpage, eg blog list, contact info
- <article> : eg a blog post, a news article
- <aside> : related to something else, eg. similar blogs
- <header> : eg nav, title tec
- <footer> : footer of the page
- <nav> : navigation links, usually ul of a hrefs

## CSS Basics

- A style sheet is a list of CSS rules/ rule sets
- **Selector**: The HTML element to which the style will be applied, eg. `p`, `h1`, `div`, `#id`, `.class`
- **declaration block**: The set of CSS properties and values enclosed in curly braces `{ }`, ending with a semicolon `;`

- in the HTML file, you can include the CSS in the `<head>` section using the `<style>` tag 
- or you can link an external CSS file using the `<link>` tag, rel-> relation, href-> path to the file

### Text and Font Styling
```css
color: black;               /* Sets text color */
background-color: yellow;   /* Sets background color */
font-size: 16px;            /* Sets font size */
font-family: Arial, sans-serif; /* Sets font family with a fallback */
text-align: center;         /* Aligns text horizontally */
text-transform: uppercase;  /* Converts text to uppercase */
line-height: 1.5;           /* Spacing between lines */
letter-spacing: 2px;        /* Spacing between letters */
text-decoration: underline; /* Adds underline to text */
```

### Multi-Column Layout
```css
column-count: 3;            /* Splits text into 3 columns */
column-gap: 20px;           /* Spacing between columns */
```

### Full Border
```css
border: 2px solid black;    /* Combines border width, style, and color */
```

### Specific Border Sides
```css
border-bottom: 1px solid black; /* Adds a solid black border at the bottom */
border-left: 8px dashed crimson; /* Adds a dashed crimson border to the left */
border-right: 2px dotted blue;  /* Adds a dotted blue border to the right */
```

### List Styling
```css
li {
    list-style-type: square;       /* Changes list bullet type to square */
    text-shadow: 2px 2px red;     /* Adds shadow with 2px offset and red color */
}
```
### inline vs Block Level Elements

- inline: span, img, strong, em, a etc
- Block-level elements: div, h1, p, ul, ol, li, table, form etc, take up the whole weight regardless of the content
- if you see the use agent stylesheet, ie directly applied by browser, you will notice display: block; by default for block level elements, and so on
- block level elements have margin to on all 4 sides, but inline only on left and right, cannot add to top and bottom
- padding: all the way around for even inline elements, padding in vertical direction kind of collapses on inline elements, it wont work as expected
- display: inline-block, sit nexts to elements, but can have padding and margin all around
- default browser styles: for accessibility

### Classes and Selectors
- eg. p.success.feedBack { } -> p tag with class success and feedback
- Descendant selector: eg. div p { } -> all p tags inside a div but not a p tag outside a div, div .class
- we can use attributes as selector, eg a[href]{ } looks for all anchor tags with href attribute
- can also do a[href="https://www.google.com"]{ } -> exact match
- or a[href^="https://"]{ } -> starts with or a[href*="google"] -> includes, or href$-> ends with
- The "cascade" means, we inherit css properties of parent, mainly fonts, textstyles, not margin padding etc
- p{
    border: inherit;
    margin: inherit; 
    color: red; // this is more specific, overrides parent
}
- the one that is further down takes precedence, but more specific selectors take precedence, eg
div p{} then p{}, div p takes precedence


### Position and Layout

- Static, Relative, Fixed, Absolute, Sticky
- Static: default, elements are positioned according to the normal flow of the document
- {
  position: relative;
  left: 20px; 
  // moves the element 20px to the right, shift away from the left
  top: 10px;
}
this would move the element relative to its original position
- if position:fixed, positions relative to the viewport, so even when you scroll, it stays in the same place
- position:fixed; -> relative to teh closest parent that has a position other than static
- sticky: mixture of static and fixed, it is relative until it reaches a certain point, then it becomes fixed
- nav{
  position: sticky;
  top: 150px; it will stick to the top of the page when it reaches 150px from the top, so if you scroll down, after a point it will stay at the top
}
- we usually use relative so that child elements can be positioned relative to the parent element
- em: takes the value inherited from parent and multiplier it by the value, eg. 1.5em, 1.5 times the inherited value
- give fixed header a z-index of 1000, so that it is always on top
- block level elements take up the whole width, so if you have some text, and you apply padding, it won't look as expected, hence use inline-block
- box-sizing: border-box; -> total width inclusive of padding and border, not just content, so that padding doesn't affect the width of the element
- max-width: 100% -> so that the image doesn't overflow the container, relative to parent
- in parent, if you have inline block elements but they still don't sit next to each other, in parent selector: white-space: nowrap;


### Pseudo Classes and Elements

- style elements when they're in a particular state

eg.
nav li a:hover{
  text-decoration: underline;
}
.images li:hover{
  position:relative;
  top: -4px; // nudge it to the top a bit
}
form input:focus{
  border: 4px dashed red;
  outline: none; // removes the default outline, better to keep it
}
form input:valid{
  border: 4px solid green;
}
nav li:first-child{
  border: 3px solid red;
}
some more: :active, :checked, :disabled, :empty, :enabled, :first-child, :last-child, :nth-child(odd), :nth-child(even), :nth-child(3), :not(p), :only-child, :only-of-type, :target, :visited

- pesudo elements allow us to inject dynamic content

eg.
article p::first-line{
  font-weight: bold;
  font-size: 1.2em;
}
section.join p::first-letter{
  font-size: 1.5em;
}
section.join p::selection{
  background-color: yellow;
  color: black; // on selecting the text
}
p::after{
  content: '...';
}

### Responsive Design and Media Queries

- Media queries allow us to apply CSS based on the viewport dimensions
- Viewport meta tag: tells the browser what the width of the viewport should be
- Responsive images: only load smaller images for mobile devices
- viewport metatag in the head:
<meta name="viewport" content="width=device-width, initial-scale=1.0">
eg.

apply at 1400 or lower
@media screen and (max-width: 1400px){
  ..{
    font-size : 40px; // increase for larger screen
  }
}
@media screen and (max-width: 700px){
  ..{
    position: relative; // instead of absolute where there might be sitting on top of another
    text-alight: center;
    padding: 10px;
  }
  .... br{
    display: none; // hide the element
  }
  ..{
    font-size: 25px; // reduce 
  }
  .. span{
    font-size: 1em; 
  }
  .images li{
    display: block; // instead of inline-block, they won't sit next to each other
  }
}

@media screen and (max-width: 560px){
  // increase for mobile devices as they  need more room to click with fingers
  nav li{
    font-size: 20px;
    display: block;
    width: 100%;
    margin: 12px 0;
  }
  header{
    position:relative;
  }
  nav{
    top: 0; // only at the very top it becomes sticky
  } 
}

### Flexbox

.nav-list{
  display:flex; // instead of block level elements they become flex items
  gap: 1rem; // space between the items
  flex-wrap: wrap; // if the items don't fit, they wrap to the next line
  margin: 0;
  padding: 0;
  list-style: none;
}
.nav-list li{
  display: block; // -> nothing changes because they have been made flex itemsj
  width: max-content; // takes the width of the content
  flex-grow: 0; // distributes left over space in parent
  flex-shrink: 1;
}
.columns > * {

  flex-basis: 1; // something like a width, but 0 takes to that intrinsic min width
}
flex-direction: column; // stack the items vertically