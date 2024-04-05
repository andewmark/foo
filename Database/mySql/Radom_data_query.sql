select * from StudentMarket.campuses;

-- Insert random data into campuses table
INSERT INTO StudentMarket.campuses (campus_name, address, city, state, country, postal_code, latitude, longitude, description, established_date)
VALUES 
('Campus A', '123 Smith St', 'Anytown', 'Anystate', 'Countryland', '12345', 40.7128, -74.0060, 'Description of Campus A', '2020-01-01'),
('Campus B', '456 Elm St', 'Othertown', 'Otherstate', 'Othercountry', '54321', 34.0522, -118.2437, 'Description of Campus B', '2018-05-10');
-- Add more rows as needed


-- Insert random data into categories table
INSERT INTO StudentMarket.categories (category_name)
VALUES 
('Category 1'),
('Category 2');
-- Add more rows as needed


-- Insert random data into users table
INSERT INTO StudentMarket.users (username, email, password, campus_id, created_at)
VALUES 
('user1', 'user1@example.com', 'password1', 1, NOW()),
('user2', 'user2@example.com', 'password2', 2, NOW());
-- Add more rows as needed


-- Insert random data into listings table
INSERT INTO StudentMarket.listings (user_id, title, description, price, category_id, status, created_at, updated_at)
VALUES 
(1, 'Listing 1', 'Description of Listing 1', 10.99, 1, 'Active', NOW(), NOW()),
(2, 'Listing 2', 'Description of Listing 2', 20.99, 2, 'Inactive', NOW(), NOW());
-- Add more rows as needed


-- Insert random data into images table
INSERT INTO StudentMarket.images (listing_id, image_url)
VALUES 
(1, 'https://example.com/image1.jpg'),
(2, 'https://example.com/image2.jpg');
-- Add more rows as needed


-- Insert random data into messages table
INSERT INTO StudentMarket.messages (sender_id, receiver_id, listing_id, message_content, created_at)
VALUES 
(1, 2, 1, 'Message content 1', NOW()),
(2, 1, 2, 'Message content 2', NOW());
-- Add more rows as needed

