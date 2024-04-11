CREATE TABLE `users` (
  `id` integer PRIMARY KEY,
  `username` varchar(255),
  `email` varchar(255),
  `password` varchar(255),
  `campus_id` integer,
  `created_at` timestamp
);

CREATE TABLE `campuses` (
  `id` integer PRIMARY KEY,
  `campus_name` varchar(255),
  `address` varchar(255),
  `city` varchar(255),
  `state` varchar(255),
  `country` varchar(255),
  `postal_code` varchar(255),
  `latitude` decimal,
  `longitude` decimal,
  `description` text,
  `established_date` date
);

CREATE TABLE `listings` (
  `id` integer PRIMARY KEY,
  `user_id` integer,
  `title` varchar(255),
  `description` text,
  `price` decimal,
  `category_id` integer,
  `status` varchar(255),
  `created_at` timestamp,
  `updated_at` timestamp
);

CREATE TABLE `categories` (
  `id` integer PRIMARY KEY,
  `category_name` varchar(255)
);

CREATE TABLE `images` (
  `id` integer PRIMARY KEY,
  `listing_id` integer,
  `image_url` varchar(255)
);

CREATE TABLE `messages` (
  `id` integer PRIMARY KEY,
  `sender_id` integer,
  `receiver_id` integer,
  `listing_id` integer,
  `message_content` text,
  `created_at` timestamp
);

ALTER TABLE `users` ADD FOREIGN KEY (`campus_id`) REFERENCES `campuses` (`id`);

ALTER TABLE `listings` ADD FOREIGN KEY (`user_id`) REFERENCES `users` (`id`);

ALTER TABLE `listings` ADD FOREIGN KEY (`category_id`) REFERENCES `categories` (`id`);

ALTER TABLE `images` ADD FOREIGN KEY (`listing_id`) REFERENCES `listings` (`id`);

ALTER TABLE `messages` ADD FOREIGN KEY (`sender_id`) REFERENCES `users` (`id`);

ALTER TABLE `messages` ADD FOREIGN KEY (`receiver_id`) REFERENCES `users` (`id`);

ALTER TABLE `messages` ADD FOREIGN KEY (`listing_id`) REFERENCES `listings` (`id`);
