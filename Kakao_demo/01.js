function solution(arr) {
  var answer = true;

  var dummyObj = {};

  arr.every(element => {
    if(dummyObj.hasOwnProperty(element)) {
      answer = false;
      return false; 
    } else {
      var tmp = {};
      tmp[element] = true;
      var newOne = Object.assign(dummyObj, tmp)
      dummyObj = newOne
      answer = true;
      return true;
    }
  });

  return answer;
}