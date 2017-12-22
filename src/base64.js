console.log(getNumber('a#'));
function getNumber(base64Num) {
    var base64itoa = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ@#";
    var base10Num = (base64itoa.indexOf(base64Num.charAt(0)) << 6) + (base64itoa.indexOf(base64Num.charAt(1)));
    return ((base10Num < 640) ? Number(base64Num) : (base10Num - 640 + 100));
}
