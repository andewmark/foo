var express = require('express');
var router = express.Router();

var app = express();

const fakeListings = [
  {
    id: 1,
    title: 'Sample Textbook - Calculus',
    price: '$25.00',
    description: 'Used Calculus textbook in excellent condition.',
    imageUrl: 'images/textbook.jpg', // Assuming an image path in your 'public' directory
    // ... other listing details
  },
  {
    id: 2,
    title: 'Used Bicycle - Great Condition',
    price: '$100.00',
    description: 'Well-maintained bicycle, perfect for students.',
    imageUrl: 'images/bicycle.jpg',
    // ... other listing details
  },
];

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('home', { title: 'Student U Marketplace' });
});

// Buying Page
router.get('/buying', function(req, res, next) {
  res.render('buying', { title: 'Student U Marketplace: Buying' });
});

// Messaging Page
router.get('/chat', function(req, res, next) {
  res.render('chat', { title: 'Student U Marketplace: Messages' });
});

// login Page
router.get('/login', function(req, res, next) {
  res.render('LogIn', { title: 'Student U Marketplace: Login' });
});


// Notifications Page
router.get('/notifications', function(req, res, next) {
  res.render('notifications', { title: 'Student U Marketplace: Listing' });
});

// Posting Page
router.get('/post', function(req, res, next) {
  res.render('post', { title: 'Student U Marketplace: Listing' });
});


// Profile Page
router.get('/profile', function(req, res, next) {
  res.render('profile', { title: 'Student U Marketplace: Listing' });
});

// Selling Page
router.get('/selling', function(req, res, next) {
  res.render('selling', { title: 'Student U Marketplace: Listing' });
});

// SignUp Page
router.get('/Signup', function(req, res, next) {
  res.render('SignUp', { title: 'Student U Marketplace: Listing' });
});

// Listing Page
router.get('/listing', function(req, res, next) {
  res.render('listing');
});


router.get('/listing/:listingId', (req, res) => {
  const listingId = parseInt(req.params.listingId); // Convert listingId to a number

  const foundListing = fakeListings.find(listing => listing.id === listingId);
  
  // Handle case where listing not found
  if (!foundListing) {
    return res.status(404).render('404');
  }

  console.log("Found Listing:", foundListing); // Log for verification


  // Render the listing page template with retrieved data
  res.render('listing', { listing: foundListing });
});



module.exports = router;
