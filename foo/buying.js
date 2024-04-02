const recent = document.querySelector('.recent-message');
const saved = document.querySelector('.saved-message');
const recentContainer = document.querySelector('.recent');
const recentLink = document.querySelector('a[href="#recent"]'); // Target specific icon within link
const savedLink = document.querySelector('a[href="#saved"]'); // Target specific icon within link



const hasRecentContent = mainContainer.children.length > 0;

if (recent.classList.contains('active')) {
    if (hasRecentContent) {
    recentContainer.style.display = 'block';
    recent.style.display = 'none'; // Hide the default "Recent Activity" message
    saved.style.display = 'none';
    } else {
    recent.style.display = 'block';
    recentContainer.style.display = 'none';
    saved.style.display = 'none';
    }
} 

else {
    document.getElementById("recent").classList.add('active')
    recent.style.display = 'block';
    saved.style.display = 'none';

    recentLink.addEventListener('click', () => {

        recent.style.display = 'block'; // Show Recent Activity
        saved.style.display = 'none';   // Hide Saved

        document.getElementById("recent").classList.add('active')
        document.getElementById("saved").classList.remove('active')
    });

    savedLink.addEventListener('click', () => {
        recent.style.display = 'none';  // Hide Recent Activity
        saved.style.display = 'block';   // Show Saved

        document.getElementById("saved").classList.add('active')
        document.getElementById("recent").classList.remove('active')
    });
}
