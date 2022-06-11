function multicheck(event)
{
    var ans = event.srcElement;
    if (ans.innerHTML == "21")
    {
        ans.style.backgroundColor = 'green';
        document.querySelector("#feedback1").innerHTML = "Correct!";
    }
    else
    {
        ans.style.backgroundColor = 'red';
        document.querySelector("#feedback1").innerHTML = "Incorrect!";
    }
}
            
function freecheck(event)
{
    var but = event.srcElement;
    let input = document.querySelector("input");
    if (input.value.toLowerCase() == "london")
    {
        but.style.backgroundColor = 'green';
        input.style.backgroundColor = 'green';
        document.querySelector("#feedback2").innerHTML = "Correct!";
                    
    }
    else
    {
        but.style.backgroundColor = 'red';
        input.style.backgroundColor = 'red';
        document.querySelector("#feedback2").innerHTML = "Incorrect!";
    }
}
