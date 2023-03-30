var left = 6, right = 40, len = 17, sleep = 25, hcnt = 200, wcnt = 1000, id = 0, canvas = document.getElementById('canvas');
var a = new Array(), b = new Array(), d = new Array(), sqs = new Array(), sx = new Array(), sy = new Array();
canvas.width = window.innerWidth;
canvas.height = window.innerHeight;
const sq = canvas.getContext('2d');
for (var j = 0; j < hcnt; ++j) {
  for (var i = 0; i < wcnt; ++i) {
    sqs[id] = canvas.getContext('2d');
    a[id] = left + Math.ceil(Math.random() * (right - left));
    b[id] = 128 + a[id];
    d[id] = 1;
    sx[id] = i * len;
    sy[id] = j * len;
    id += 1;
  }
}
function cc() {
  for (var i = 0; i < hcnt * wcnt; ++i) {
    sqs[i].fillStyle = 'rgba(255, ' + b[i] + ', ' + 2 * a[i] + ', 1)';
    sqs[i].fillRect(sx[i], sy[i], len, len);
    a[i] += d[i] * Math.ceil(Math.random() * 3);
    b[i] = 128 + a[i];
    if (a[i] >= right) d[i] = -1;
    if (a[i] <= left) d[i] = 1;
  }
}
setInterval(cc, sleep);
