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
