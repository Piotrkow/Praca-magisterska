
            jQuery(document).ready(function() {
                //jQuery('a').not('a[href^="http://www.spidersweb.pl"]').not(".szary a.dark.big").not('.nonew').attr( 'target','_blank' );
                var scroll = jQuery(document).scrollTop();
                var zapytaj = jQuery('#zapytaj');
                var p = jQuery("section.section");
                var p_height = jQuery('section.section').height();
                var position = p.offset();

                var zapytaj_height = zapytaj.height();
                var zapytaj_position = zapytaj.offset();
                var zapytaj_trigger = zapytaj_position + zapytaj_height;
                var footer = jQuery('footer');
                var footer_postion = footer.offset();
                                var footer_trigger = position.top + p_height - 400;
                                jQuery(document).scroll(function() {
                    scroll = jQuery(document).scrollTop();
                    footer_postion = footer.offset();
                    p_height = jQuery('section.section').height();
                                        var footer_trigger = position.top + p_height - 400;
                    
                    if (zapytaj_trigger < scroll && scroll < footer_trigger) {
                        jQuery('.scroll').css({
                            "position": "fixed",
                            "top": "70px",
                        });
                    }
                    else {
                        jQuery('.scroll').css({
                            "position": "static",
                            "top": "0px",
                        });
                    }
                    /*var question_height = $("#start").height();
                    if (scroll > question_height) {
                        jQuery('.scroll').css({
                            "position": "static",
                            "top": "0px",
                            "display": "none"
                        });
                    }else{
                        jQuery('.scroll').css({
                            "display": "block"
                        });
                    }*/
                });
            });
            jQuery(document).ready(function() {
                var article_height = jQuery('#start').height() + 1;
                var scroll_article = jQuery(document).scrollTop();
                var perc = scroll_article / article_height * 100;
                if (perc > 100) {
                    perc = 100;
                }
                perc_ret = perc + '%';
                jQuery('.progressbar-inner').css('width', perc_ret);
                jQuery(document).scroll(function() {
                    scroll_article = jQuery(document).scrollTop();
                    perc = scroll_article / article_height * 100;
                    console.log(perc);
                    if (perc > 100) {
                        perc = 100;
                    }
                    perc_ret = perc + '%';
                    jQuery('.progressbar-inner').css('width', perc_ret);
                });
            });

            jQuery().ready(function(){
                jQuery('div.ui-loader').remove();
                jQuery('#mainnav').hide();
                var header_height = 130;
                var scroll = jQuery(document).scrollTop();
                if(scroll>header_height){
                        jQuery('#mainnav').show();
                    } else {
                        jQuery('#mainnav').hide();
                    }

                jQuery( window ).scroll(function() {
                    header_height = 130
                    scroll = jQuery(document).scrollTop();
                    if(scroll>header_height){
                        jQuery('#mainnav').fadeIn('fast');
                    } else {
                        jQuery('#mainnav').hide();
                    }
                });
            });

        