//regular objects
function Iterator(array){
  let index = 0;      //closure gör index privat

  return{
    hasNext: function(){
      return index < array.length;
    },
    next: function(){
      if(this.hasNext()){
        return array[index++];
      }
      return null;
    }
  };
}

const arr1 = [1,2,3,4,5,6];
const it = Iterator(arr1);

while(it.hasNext()){
  console.log(it.next());
}
