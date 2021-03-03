function isPrime(num) {
  for(i=0; i<30; i++){
    var start = Date.now();
    if (num <= 3) return num > 1;
    
    if ((num % 2 === 0) || (num % 3 === 0)) return false;
    
    let count = 5;
    
    while (Math.pow(count, 2) <= num) {
      if (num % count === 0 || num % (count + 2) === 0) return false;
      
      count += 6;
    }
  
    var end = Date.now();
    var tempo = end-start;
    console.log("Tempo: " + tempo);
  }
  return true;
}

var teste = isPrime(2147483647);
console.log(teste);
