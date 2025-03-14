// prototype-based Iterator
function Iterator(array) {
  this.array = array;
  this.index = 0;
}

Iterator.prototype.hasNext = function() {
  return this.index < this.array.length;
};

Iterator.prototype.next = function() {
  return this.array[this.index++];
};

Array.prototype.iterator = function() {
  return new Iterator(this);
};

const arr2 = [1,2,3,4, 5, 6];

const it2 = arr2.iterator();

while(it2.hasNext()) {
  console.log(it2.next());
}