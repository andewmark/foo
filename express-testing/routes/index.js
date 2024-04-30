var express = require('express');
var router = express.Router();
const websocketService = require('../bin/websocket');
const currUser=7;

const fakeListings = [];

//let User_listings ="SELECT * from listings WHERE user_id = 6;";


// websocketService.on('close', (ws) => { 
//   this.handleConnectionClose(ws);
// });
let User_listings = "SELECT listings.*, users.username, users.ratings, users.residence_hall FROM listings JOIN users ON listings.user_id = users.id";
websocketService.on('connected', () => {

  websocketService.sendRequests(User_listings);
  websocketService.on('dataReceived', (Data) => {
    // console.log(Data);

    /* GET home page. */
  router.get('/', function(req, res, next) {
    res.render('home', {fakeListings: Data});
  });

  // Listing Page
  router.get('/listing', function(req, res, next) {
    res.render('listing');
  });
  
  
  router.get('/listing/:listingId', (req, res) => {
    const listingId = parseInt(req.params.listingId); // Convert listingId to a number
  
    const foundListing = Data.find(listing => listing.id === listingId);
  
    
    // Handle case where listing not found
    if (!foundListing) {
      return res.status(404).render('404');
    }
  
    console.log("Found Listing:", foundListing); // Log for verification
  
  
    // Render the listing page template with retrieved data
    res.render('listing', { listing: foundListing });
  });

  });

});



websocketService.on('connected', () => {

  let UserSaved = "SELECT savings.*, listings.price, listings.title, users.residence_hall, listings.image_url FROM savings JOIN users ON savings.user_id = users.id JOIN listings ON savings.listing_id = listings.id WHERE savings.user_id ="+ currUser+";";
  websocketService.sendRequests(UserSaved);

  websocketService.on('dataReceived', (Data_savings) => {
    // printing out savings data
    console.log(Data_savings);
      // Buying Page
    router.get('/buying', (req, res, next) => {
        res.render('buying', {listings: Data_savings});
    });
    
  });

});

  

  // Query for saved: 1 : 1 -> userid,listingid,price,title,residence_hall,imageurl
  







// /* GET home page. */
// router.get('/', function(req, res, next) {
// res.render('home', {fakeListings: fakeListings});
// });



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
res.render('selling', { fakeListings: fakeListings});
});

// SignUp Page
router.get('/Signup', function(req, res, next) {
res.render('SignUp', { title: 'Student U Marketplace: Listing' });
});


  

  

    
 




module.exports = router;
