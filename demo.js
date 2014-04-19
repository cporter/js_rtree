
var rtree = new Module.RTree();
var nearest = rtree.FindNearest ([0, 0, 0]);
console.log("nearest: " + nearest);


for (var i = 1; i < 20; ++i)
    rtree.AddPoint(i, [i*i, i*i, i*i]);
nearest = rtree.FindNearest ([0, 0, 0]);
console.log("nearest: " + nearest);

rtree.AddPoint(100, [0.5, 0.5, 0.2]);
nearest = rtree.FindNearest ([0, 0, 0]);
console.log("nearest: " + nearest);
