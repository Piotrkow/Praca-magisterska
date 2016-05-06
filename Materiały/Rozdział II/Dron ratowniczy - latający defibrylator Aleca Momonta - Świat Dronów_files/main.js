/* -----------------------------------------------------------------------------
 * Document ready
 * -------------------------------------------------------------------------- */
// Set jQuery to NoConflict Mode
jQuery.noConflict();

;(function( $, window, document, undefined ){
	"use strict";

	$.fn.vwPaginationAjax = function() {
		function progressiveAnimate(items, reverse) {
			var i = 0;

			if (reverse) {
				items = $(items.get().reverse());
			}

			items.each(function(){
				var $this = $(this);

				if (reverse) {
					$this.stop().delay( i + '').fadeTo(150, 0);
				} else {
					$this.stop().delay( i + '').fadeTo(150, 1);
				}

				i = i + 100;
			});
		}

		$( this ).on( 'click', '.vw-page-navigation-pagination a', function( e ) {
			e.preventDefault(); // prevent default linking
			var $this = $( this );
			var link = $this.attr( 'href' );
			var $viewport = $('html, body');
			var $container = $this.closest( '.vwspc-section, .vw-post-shortcode' );
			var container_id = $container.attr( 'id' );

			if ( $container.hasClass( 'vwspc-section' ) ) {
				var placeholder = '#'+container_id+' .vwspc-section-content';
				var $post_container = $container.find( '.vwspc-section-content .vw-post-loop' );
				var $controls = $container.find( '.vwspc-section-content .vw-post-loop > *, .vwspc-section-content .vw-page-navigation' );

			} else { // hasClass( 'vw-post-shortcode' )
				var placeholder = '#'+container_id;
				var $post_container = $container.find( '.vw-post-loop' );
				var $controls = $container.find( '.vw-post-loop > *, .vw-page-navigation' );

			}

			$viewport
				.animate( { scrollTop: $container.offset().top - 60 }, 1700, "easeOutQuint")
				.bind("scroll mousedown DOMMouseScroll mousewheel keyup", function (e) {
					if (e.which > 0 || e.type === "mousedown" || e.type === "mousewheel") {
						$viewport.stop().unbind('scroll mousedown DOMMouseScroll mousewheel keyup');
					}
				});

			$controls.fadeTo( 500, 0, function() {
				$( this ).css('visibility', 'hidden');
			} );
			$post_container.addClass( 'vw-preloader-bg' );

			$( placeholder ).load( link + ' ' + placeholder + '>*', function( response, status, xhr ) {
				if( status == 'success' ) {
					$( '.vw-isotope' ).vwIsotope();
					$container.removeClass( 'vw-preloader-bg' );
				}

				if( status == 'error' ) {
					console.log( 'Error: '+xhr.status+': '+xhr.statusText );
				}
			} );
		} );
	}

	$.fn.vwIsotope = function() {
		if ( $.fn.isotope ) {
			var $isotope_list = $( this );
			$isotope_list.imagesLoaded( function () {
				$isotope_list.isotope();

				$( window ).resize( function() {
					$isotope_list.isotope( 'layout' );
				} );
			});
		}
	};

	$.fn.vwSticky = function() {
		if ( $.fn.sticky ) {
			var $sticky_bar = $( this );
			var $sticky_wrapper = false;
			var offset = 0;

			if ( $( '#wpadminbar' ).length ) {
				offset = $( '#wpadminbar' ).height();
			}
			
			$sticky_bar.addClass( 'vw-sticky' ).sticky( {
				wrapperClassName: 'vw-sticky-wrapper',
				topSpacing: offset,
			} );

			$( window ).resize( function() {
				if ( ! $sticky_wrapper ) $sticky_wrapper = $( '.vw-sticky-wrapper' );
				$sticky_wrapper.css('height', $sticky_bar.outerHeight());
				$sticky_bar.sticky( 'update' );
			} );
		}
	}

	$.fn.vwBxSlider = function( options ) {
		var default_options = {
			mode: 'horizontal',
			speed: parseInt( vw_main_js.bxslider_transition_speed ),
			adaptiveHeight: true,
			auto: parseInt( vw_main_js.bxslider_auto_start ),
			autoControls: false,
			autoHover: parseInt( vw_main_js.bxslider_pause_on_hover ),
			captions: false,
			controls: true,
			infiniteLoop: true,
			minSlides: 1,
			moveSlides: 0,
			pager: false,
			pause: parseInt( vw_main_js.bxslider_slide_duration ),
			preloadImages: "visible",
			nextText: '<i class="icon-iconic-right"></i>',
			prevText: '<i class="icon-iconic-left"></i>',
			slideMargin: 0,
			touchEnabled: true,
			preventDefaultSwipeX: true,
			preventDefaultSwipeY: false,
			oneToOneTouch: true,
			responsive: true,
			useCSS: false,
		}

		this.each( function () {
			var $this = $( this );
			
			$this.find( '.vw-bxslider-slides' ).bxSlider( $.extend( {
				onSliderLoad: function() {
					$this.animate( {
						'opacity': 1,
						'height': $this.find( '.vw-bxslider-slides > li:first-child' ).height(),
					}, 500, function() {
						$this.removeClass( 'vw-bxslider-loading' );
						$this.css( {
							'opacity': '',
							'height': '',
						} );
					} );
					
				}
			}, default_options, options ) );

		} );
	}

	// Initial all scripts
	$( window ).load( function () {
		if ( $.fn.bxSlider ) {
			// Lazy load to avoid invalid size issue
			$('.vw-post-loop-slider-carousel').vwBxSlider( {
				slideWidth: 360,
				minSlides: 1,
				maxSlides: 4,
				moveSlides: 1,
				slideMargin: 10,
			} );
		}
	});

	$( document ).ready( function () {
		// Slider
		if ( $.fn.bxSlider ) {
			$('.vw-post-loop-slider-large, .vw-embeded-gallery.vw-bxslider').vwBxSlider( {
				slideWidth: 0,
				mode: 'fade',
				minSlides: 1,
				maxSlides: 1,
				moveSlides: 1,
			} );
		}

		// ImgLiquid
		if ( $.fn.imgLiquid ) {
			$( '.vw-post-loop-slider-large .vw-post-style-slide' ).imgLiquid();
		}

		// Breaking News
		if ( $.fn.newsTicker ) {
			$('.vw-breaking-news-list').newsTicker( {
				row_height: 29,
				max_rows: 1,
				speed: 600,
				direction: 'up',
				duration: 4000,
				autostart: 1,
				pauseOnHover: 1
			} ).addClass( 'loaded' );
		}

		if ( $.fn.mmenu ) {
			$(".vw-menu-mobile-wrapper").mmenu({
				classes: "mm-slide",
				offCanvas: {
					position: "right",
					// zposition : "front",
				},
				// clone:true,
				// searchfield: true
			});

			$(".vw-mobile-nav-button").click(function() {
				$(".vw-menu-mobile-wrapper").trigger("open.mm");
			});
		}

		if ( $.fn.backstretch ) {
			$( '.vwspc-section-full-page-link' ).each( function () {
				var $this = $( this );
				var background_url = $this.find( 'img.vw-full-page-link-background' ).attr( 'src' );

				if ( background_url ) {
					$this.backstretch( background_url, {
						fade: vw_main_js.VW_CONST_BACKSTRETCH_OPT_FADE,
						centeredY: vw_main_js.VW_CONST_BACKSTRETCH_OPT_CENTEREDY,
						centeredX: vw_main_js.VW_CONST_BACKSTRETCH_OPT_CENTEREDX,
						duration: vw_main_js.VW_CONST_BACKSTRETCH_OPT_DURATION,
					} );
				}
			} );
		}

		// Sticky Bar
		$( '.vw-menu-main-wrapper' ).vwSticky();

		// FitVids
		if ( $.fn.fitVids ) {
			$( '.vw-embeded-media, .vw-featured-image-wrapper, .flxmap-container, .comment-body, .vw-post-content, #footer' ).fitVids( { customSelector: "iframe[src*='maps.google.'],iframe[src*='soundcloud.com']" } );
		}

		// -----------------------------------------------------------------------------
		// Isotope - Mansonry grid
		// 
		$( '.vw-isotope' ).vwIsotope();

		// MagnificPopup
		if ( $.fn.magnificPopup ) {
			$( '.vw-post-meta-icon.vw-post-share-count' ).magnificPopup({
				type: 'inline',

				fixedContentPos: false,
				fixedBgPos: true,

				overflowY: 'auto',

				closeBtnInside: true,
				preloader: false,
				
				midClick: true,
				removalDelay: 300,
				mainClass: 'my-mfp-zoom-in'
			}).click( function( e ) {
				e.preventDefault();
			} );


			// Add light box to featured image
			$( "body.single .vw-page-content a[href*='.png'], body.single .vw-page-content a[href*='.jpg'], body.single .vw-page-content a[href*='.jpeg'], .vw-custom-tiled-gallery a, .vw-embeded-gallery.vw-bxslider .vw-bxslider-slides a" ).magnificPopup({
				type: 'image',
				closeOnContentClick: true,
				gallery: {
					enabled: true,
					navigateByImgClick: true,
					preload: [0,1] // Will preload 0 - before current, and 1 after the current image
				},
				image: {
					verticalFit: true,
					titleSrc: function( item ) {
						var title = item.el.attr('title');
						if ( ! title ) {
							title = $( 'img', item.el ).attr('alt');
						}

						return title;
					}
				}
			});
		}

		if ( $.fn.superfish ) {
			$('.vw-menu-location-top').superfish({
				delay:       800,                            // one second delay on mouseout
				animation:   {opacity:'show',height:'show'},  // fade-in and slide-down animation
				speed:       'fast',                          // faster animation speed
				autoArrows:  false                            // disable generation of arrow mark-up
			});

			$('.vw-menu-location-main').superfish({
				popUpSelector: '.sub-menu-wrapper',
				delay:       800,                            // one second delay on mouseout
				animation:   {opacity:'show',height:'show'},  // fade-in and slide-down animation
				speed:       'fast',                          // faster animation speed
				autoArrows:  false                            // disable generation of arrow mark-up
			});
		}

		//  Instant search
		if ( $.fn.instant_search ) {
			$( '.vw-instant-search-buton' ).instant_search();
		}

		// Ajax pagination
		if ( $.fn.vwPaginationAjax ) {
			$( '.vwspc-section' ).vwPaginationAjax();
		}

		// Widget Tabs
		if ( $.fn.tabs ) {
			$( ".vw-post-tabed" ).tabs( {
				show: { effect: "fade", duration: 300 }
			} );
		}

		// Wordpress gallery grid
		$( '.vw-custom-tiled-gallery' ).each( function ( i, el ) {
			var $gallery =  $( el );
			var layout = $gallery.attr( 'data-gallery-layout' );
			if ( ! ( parseInt( layout, 10 ) > 0 ) ) {
				layout = '213'; // Default layout
			}

			layout = layout.split('');
			var columnLayout = [];
			for (var i in layout ) {
				var columnCount = parseInt( layout[i], 10 );
				var columnWidth = 100.0 / columnCount;
				for ( var j = 1; j <= columnCount; j++ ) {
					columnLayout.push( columnWidth );
				}
			}

			$gallery.find( '> figure' ).each( function( i, el ) {
				var $el = $( el );
				var layoutIndex = i % columnLayout.length;
				$el.css( 'width', columnLayout[ layoutIndex ] - 1 + '%' );
			} );
		} );

		// Full page link section
		$( '.vwspc-section-full-page-link' ).click( function() {
			window.location = $( this ).find( 'a' ).eq(0).attr( 'href' );
		} );

		// -----------------------------------------------------------------------------
		// Tipsy
		// 
		if ( $.fn.tipsy ) {
			$('.widget_vw_widget_author_list a, .vw-author-socials a, .vw-category-link, .vw-author-avatar, .author-name, .vw-post-date, .vw-post-shares-social, .bbp-author-avatar, .vw-post-comment-count, .vw-post-likes-count, .vw-post-view-count, .vw-post-share-count').tipsy( {
				fade: true,
				gravity: 's',
			} );
		}

		// -----------------------------------------------------------------------------
		// Sticky Sidebar
		// 
		if ( $.fn.hcSticky ) {
			var offset = 15;

			if ( $( '#wpadminbar' ) ) {
				offset += $( '#wpadminbar' ).height();
			}

			if ( $( 'body.vw-site-enable-sticky-menu' ) ) {
				offset += $( '#vw-menu-main-sticky-wrapper' ).height();
			}

			$(".vwspc-section-sidebar .vw-sticky-sidebar, .vw-page-wrapper .vw-sticky-sidebar").hcSticky( {
				stickTo: '.container',
				wrapperClassName: 'vw-sticky-sidebar-wrapper',
				offResolutions: [-992],
				top: offset,
			} );
		}
	} );

})( jQuery, window , document );