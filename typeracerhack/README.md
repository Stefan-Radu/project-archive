## How to 'win' every race on typeracer.com

I've been working on my typing skills using [typeracer.com](typeracer.com) for quite a while now, and that allowed me to encounter some unbeatable opponents. And by unbeatable, I mean 300+ WPM unbeatable :O (at least compared to my humble 70 WPM). I assumes they hacked the system and then played around searching for how that may have been done.

I came up with the following piece of code. It extracts the text and inserts it into the input field.

``` javascript
function getElementByXpath(path) {
  return document.evaluate(path, document, null, 
    XPathResult.FIRST_ORDERED_NODE_TYPE, null).singleNodeValue;
}

str = getElementByXpath("//span[@unselectable='on']").innerText;
str += getElementByXpath("//span[@unselectable='on' and " + 
  "(contains(text(), '.') or contains(text(), '?') or " +
  "contains(text(), '!'))]").innerText;
inp = getElementByXpath("//input[@class='txtInput']")
inp.value = str;
```

#### Keep in mind this is a proof of concept with educational purposes only. Use this exclusively in practice mode.

To use it follow the steps below:
1. Start a race
2. When the countdown finished click the input field (this is kind mandatory)
3. Press `F12`, paste the code and execute by pressing enter.
4. Hover the input filed with your mouse, when you feel like winning.

And voila. I managed to easily reach 380 WPM with this. The site, however won't take your score into consideration if you don't pass a verification test afterwards (for WPM > 100). This is expected and good, since we don't want any cheaters around on the scoreboard :P
