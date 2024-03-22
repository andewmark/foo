        const recent = document.querySelector('.recent');
        const saved = document.querySelector('.saved');
        const recentLink = document.querySelector('a[href="#recent"]'); // Target specific icon within link
        const savedLink = document.querySelector('a[href="#saved"]'); // Target specific icon within link

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