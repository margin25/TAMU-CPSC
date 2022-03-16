
function init() {
    console.log("init!");
    const links = document.querySelectorAll('.link');
    const sections = document.querySelectorAll('section');
    
    let activeLink = 0;

    links.forEach((link,i) =>{
        link.addEventListener('click', () => { 
           if(activeLink != i){
               links[activeLink].classList.remove('active');
               links[activeLink].classList.add('active');
               sections[activeLink].classList.remove('active');
               setTimeout(() => {
                   activeLink = i;
                   sections[i].classList.add('active');
                }, 0);
            }
        })
    });
}

// switch between two css 

function toggleTheme() {
    // Obtains an array of all <link>
    // elements.
    // Select your element using indexing.
    var theme = document.getElementsByTagName('link')[0];

    // Change the value of href attribute 
    // to change the css sheet.
    if (theme.getAttribute('href') == 'style.css') {
        theme.setAttribute('href', 'light.css');
    } else {
        theme.setAttribute('href', 'style.css');
    }
}

window.onload = init;