CREATE TABLE `users` (
  `id` INTEGER PRIMARY KEY AUTO_INCREMENT,
  `username` VARCHAR(255),
  `email` VARCHAR(255),
  `password` VARCHAR(255),
  `campus_id` INTEGER,
  `name` VARCHAR(255),
  `profile_url` VARCHAR(255),
  `created_at` TIMESTAMP,
  FOREIGN KEY (`campus_id`) REFERENCES `campuses` (`id`)
);

CREATE TABLE `campuses` (
  `id` INTEGER PRIMARY KEY AUTO_INCREMENT,
  `campus_name` VARCHAR(255),
  `address` VARCHAR(255),
  `city` VARCHAR(255),
  `state` VARCHAR(255),
  `country` VARCHAR(255),
  `postal_code` VARCHAR(255),
  `latitude` DECIMAL,
  `longitude` DECIMAL,
  `description` VARCHAR(255),
  `established_date` DATE
);

CREATE TABLE `listings` (
  `id` INTEGER PRIMARY KEY AUTO_INCREMENT,
  `user_id` INTEGER,
  `title` VARCHAR(255),
  `description` TEXT,
  `price` DECIMAL,
  `category_id` INTEGER,
  `status` VARCHAR(255),
  `condition` VARCHAR(255), -- Added the condition column
  `created_at` TIMESTAMP,
  `updated_at` TIMESTAMP,
  `image_url` VARCHAR(255),
  FOREIGN KEY (`user_id`) REFERENCES `users` (`id`),
  FOREIGN KEY (`category_id`) REFERENCES `categories` (`id`)
);

CREATE TABLE `categories` (
  `id` INTEGER PRIMARY KEY AUTO_INCREMENT,
  `category_name` VARCHAR(255)
);

-- CREATE TABLE `images` (
--   `id` INTEGER PRIMARY KEY AUTO_INCREMENT,
--   `listing_id` INTEGER,
--   `image_url` VARCHAR(255),
--   FOREIGN KEY (`listing_id`) REFERENCES `listings` (`id`)
);

CREATE TABLE `messages` (
  `id` INTEGER PRIMARY KEY AUTO_INCREMENT,
  `sender_id` INTEGER,
  `receiver_id` INTEGER,
  `listing_id` INTEGER,
  `message_content` TEXT,
  `created_at` TIMESTAMP,
  FOREIGN KEY (`sender_id`) REFERENCES `users` (`id`),
  FOREIGN KEY (`receiver_id`) REFERENCES `users` (`id`),
  FOREIGN KEY (`listing_id`) REFERENCES `listings` (`id`)
);

-- New table for savings
CREATE TABLE `savings` (
  `id` INTEGER PRIMARY KEY AUTO_INCREMENT,
  `user_id` INTEGER,
  `listing_id` INTEGER,
  FOREIGN KEY (`user_id`) REFERENCES `users` (`id`),
  FOREIGN KEY (`listing_id`) REFERENCES `listings` (`id`)
);
